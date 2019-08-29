#include "server/listener.h"

Listener::Listener(int16_t port, unsigned int max_connection_count) : 
	_port(port),
	_max_connection_count(max_connection_count),
	_socket(-1),
	_status(false)
{
	if (_max_connection_count == 0) {
		throw std::invalid_argument("Max connections can't be none.");
	}
}

Listener::~Listener() {
	stop();
}

bool Listener::start() {
	if (_status) return false;

	if (!_create()) return false;
	if (!_bind()) return false;

	if (listen(_socket, _max_connection_count) < 0) {
		return false;
	}

	_status = true;
	return true;
}

bool Listener::stop() {
	if (!_status) return false;
	
	shutdown(_socket, SHUT_RD);
	close(_socket);
	_socket = -1;

	_status = false;
	return true;
}

int Listener::acquire() {
	int address_size = sizeof(_address);
	return accept(_socket, (struct sockaddr*) &_address, (socklen_t*) &address_size);
}

bool Listener::_create() {
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);

	int socket_tmp = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_tmp == 0) return false;

	int opt = 1;

	if (setsockopt(socket_tmp, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		return false;
	}

	_socket = socket_tmp;
	return true;
}

bool Listener::_bind() {
	if (bind(_socket, (struct sockaddr*) &_address, sizeof(_address)) < 0) {
		return false;
	}
	return true;
}