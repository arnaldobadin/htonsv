#include "listener.h"

Listener::Listener(int16_t port) : 
	_port(port),
	_socket(-1) {

	if (!_createSocket(_socket)) {
		throw std::runtime_error("Failed to create socket.");
	}

	_address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port);

	if (!_bindSocket(_socket)) {
		throw std::runtime_error("Failed to bind socket.");
	};

	_status = true;
	_listen = false;
}

Listener::~Listener() {
	stop();
	close(_socket);
	_socket = -1;
}

bool Listener::start(unsigned int max_connections) {
	if (_listen) return false;

	if (listen(_socket, max_connections) < 0) {
		return false;
	}

	_listen = true;
	return true;
}

bool Listener::stop() {
	if (!_status) return false;
	
	shutdown(_socket, SHUT_RD);

	_listen = false;
	_status = false;
	return true;
}

int Listener::acquire() {
	int address_size = sizeof(_address);
	return accept(_socket, (struct sockaddr*) &_address, (socklen_t*) &address_size);
}

bool Listener::_createSocket(int& socket_in) {
	int socket_tmp = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_tmp == 0) return false;

	int opt = 1;

	if (setsockopt(socket_tmp, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		return false;
	}

	socket_in = socket_tmp;
	return true;
}

bool Listener::_bindSocket(int socket_in) {
	if (!socket_in) return false;

	if (bind(socket_in, (struct sockaddr*) &_address, sizeof(_address)) < 0) {
		return false;
	}

	return true;
}