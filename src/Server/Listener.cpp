#include "Listener.h"

Listener::Listener(int16_t port) : 
	_port(port),
	_socket(-1) {

	if (!_doCreateSocket(_socket)) {
		Logger::doSendMessage(Logger::TYPES::ERROR, "Failed to create socket on Listener::Constructor.");
	}

	_address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port);

	if (!_doBindSocket(_socket)) {
		Logger::doSendMessage(Logger::TYPES::ERROR, "Failed to bind socket on Listener::Constructor.");
	};

	_status = true;
}

Listener::~Listener() {
	doStop();
	close(_socket);
	_socket = -1;
}

int Listener::doAccept() {
	int address_size = sizeof(_address);
	return accept(_socket, (struct sockaddr*) &_address, (socklen_t*) &address_size);
}

int Listener::doListen(unsigned int max_connections) {
	return listen(_socket, max_connections);
}

bool Listener::doStop() {
	if (!_status) return false;
	shutdown(_socket, SHUT_RD);
	_status = false;
	return true;
}

bool Listener::_doCreateSocket(int& socket_in) {
	int socket_tmp = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_tmp == 0) return false;

	int opt = 1;

	if (setsockopt(socket_tmp, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		return false;
	}

	socket_in = socket_tmp;
	return true;
}

bool Listener::_doBindSocket(int socket_in) {
	if (!socket_in) return false;

	if (bind(socket_in, (struct sockaddr*) &_address, sizeof(_address)) < 0) {
		return false;
	}

	return true;
}