#include "Server/Server.h"

Server::Server(std::uint16_t port, unsigned int max_connections, unsigned int thread_count) : 
    _port(port),
    _max_connections(max_connections),
    _thread_count(thread_count),
    _signal(false),
    _listen(false)
{
	if (max_connections == 0) {
		Logger::doSendMessage(Logger::TYPES::ERROR, "Max connections can't be none on Server::Constructor.");
	}

	_listener = std::unique_ptr<Listener>(new Listener(_port));
}

Server::~Server() {
	doStop();

	_listener->doStop();

	try {
		if (_thread_consume.joinable()) {
			_thread_consume.join();
		}

		for (std::thread& thread_process : _thread_process) {
			if (thread_process.joinable()) {
				thread_process.join();
			}
		}
	} catch (...) {}
}

bool Server::setRoute(const std::string& path, Struct::Methods method, std::function<void(Request*, Response*)> callback) {
	for (const Route& value : _routes) {
		if (value.path == path && value.method == method) {
			return false;
		}
	}

	Server::Route route = {path, method, callback};
	if (!route.isValid()) return false;

	_routes.push_back(route);
	return true;
}

bool Server::getRoute(const std::string& path, Struct::Methods method, Server::Route& route) {
	for (const Route& value : _routes) {
		if (value.path == path && value.method == method) {
			route = value;
			return true;
		}
	}

    return false;
}

bool Server::doListen() {
	if (_listen) return false;

	if (_listener->doListen(_max_connections) < 0) {
		return false;
	}

	_listen = true;

	Logger::doSendMessage(Logger::TYPES::INFO, "Server running with success at port " + std::to_string(_port) + ".");

	_thread_consume = std::thread(&Server::_doConsumeSocket, this);
	for (size_t i = 0; i < _thread_count; i++) {
		_thread_process.push_back(std::thread(&Server::_doProcessSocket, this));
	}

	return true;
}

bool Server::doStop() {
	if (!_listen) return false;
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_listen = false;
	}
	_condition.notify_one();
	return true;
}

void Server::_doConsumeSocket() {
	int socket_in = -1;

	while (_listen) {
		socket_in = _listener->doAccept();

		{
			std::lock_guard<std::mutex> lock(_mutex);
			_queue.push_back(socket_in);
			_signal = true;
		}

		_condition.notify_one();
	}
}

void Server::_doProcessSocket() {
	while (_listen) {
		int queue_size = 0;

		{
			std::unique_lock<std::mutex> lock(_mutex);
			_condition.wait(lock,
				[this] {
					if (this->_signal) return true;
					if (!this->_listen && !this->_queue.size()) return true;
					return false;
				}
			);
			queue_size = _queue.size();
		}

		if (!queue_size) {
			{
				std::lock_guard<std::mutex> lock(_mutex);
				_signal = false;
			}
			
			_condition.notify_one();
			continue;
		}

		int socket_in = -1;
		{
			std::lock_guard<std::mutex> lock(_mutex);
			socket_in = _queue[0];
			_queue.erase(_queue.begin());
		}

		Request request(socket_in);
		Response response(socket_in);
		
		_doProcessRequest(&request, &response);

		close(socket_in);
	}
}

bool Server::_doProcessRequest(Request* request, Response* response) {
	if (!request->isValid()) {
		response->doSendError(HttpStatus::Code::BadRequest, "Invalid request.");
		return false;
	}

	std::string path = request->getPath();
	Struct::Methods method = request->getMethod();

	Server::Route route;
	if (!getRoute(path, method, route)) {
		response->doSendError(HttpStatus::Code::Forbidden, "Path invalid/not found.");
		return false;
	}

	route.callback(request, response);

	if (!response->isSent()) {
		response->doSendError(HttpStatus::Code::ServiceUnavailable, "Resource was not found or can't respond now.");
	}

	return true;
}