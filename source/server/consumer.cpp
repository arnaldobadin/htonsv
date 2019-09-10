#include "htonsv/server/consumer.h"

Htonsv::Consumer::Consumer(std::uint16_t port, std::function<void(int)> callback) : 
	_port(port),
	_socket(-1),
	_status(false),
	_max_connection_count(MAX_CONNECTION_COUNT_DEFAULT),
	_signal(false),
	_callback(callback)
{
	unsigned int thread_count = std::thread::hardware_concurrency();
	if (thread_count < 1) thread_count = THREAD_COUNT_DEFAULT;
	_thread_count = thread_count;

	_listener = std::unique_ptr<Listener>(new Listener(_port, _max_connection_count));
}

Htonsv::Consumer::~Consumer() {
	stop();
}

bool Htonsv::Consumer::start() {
	if (_status) return false;

	if (!_listener->start()) {
		return false;
	}

	_status = true;

	_thread_consume = std::thread(&Htonsv::Consumer::_consume, this, "consumer");
	for (size_t i = 0; i < _thread_count; i++) {
		_threads_process.push_back(
			std::thread(&Htonsv::Consumer::_process, this, ("worker-" + std::to_string(i)))
		);
	}

	return true;
}

bool Htonsv::Consumer::stop() {
	if (!_status) return false;

	if (!_listener->stop()) {
		return false;
	}

	_status = false;

	while (!_queue.empty()) {
		close(_queue.front());
		_queue.pop();
	}

	try {
		if (_thread_consume.joinable()) {
			_thread_consume.join();
		}

		_condition.notify_all();

		for (std::thread& thread_process : _threads_process) {
			if (thread_process.joinable()) {
				thread_process.join();
			}
		}
	} catch(...) {}

	return true;
}

void Htonsv::Consumer::_consume(const std::string& name) {
	int socket_in = -1;

	while (_status) {
		socket_in = _listener->acquire();

		if (socket_in < 1) {
			continue;
		}

		{
			std::lock_guard<std::mutex> lock(_mutex);
			_queue.push(socket_in);
		}

		_condition.notify_all();
	}
}

void Htonsv::Consumer::_process(const std::string& name) {
	int socket_in = -1;

	while (_status) {
		{
			std::unique_lock<std::mutex> lock(_mutex);

			if (_queue.empty()) {
				_condition.wait(lock,
					[this] {return !_queue.empty() || !_status;}
				);
			}

			socket_in = _queue.front();
			_queue.pop();
		}

		if (socket_in < 1) {
			continue;
		}

		_callback(socket_in);

		close(socket_in);
	}
}