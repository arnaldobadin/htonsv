#include "htonsv/server/server.h"

Server::Server(std::uint16_t port) : 
    _port(port),
    _status(false)
{
	_consumer = std::unique_ptr<Consumer>(
		new Consumer(_port, [this] (int socket_in) {this->_process(socket_in);})
	);
}

Server::~Server() {
	stop();
}

bool Server::setRoute(const std::string& path, Protocol::Item method, std::function<void(Request*, Response*)> callback) {
	for (const Route& value : _routes) {
		if (value.path == path && value.method.id == method.id) {
			return false;
		}
	}

	Server::Route route = {path, method, callback};
	if (!route.valid()) return false;

	_routes.push_back(route);
	return true;
}

bool Server::getRoute(const std::string& path, Protocol::Item method, Server::Route& route) {
	for (const Route& value : _routes) {
		if (value.path == path && value.method.id == method.id) {
			route = value;
			return true;
		}
	}

    return false;
}

bool Server::start() {
	if (_status) return false;

	if (!_consumer->start()) {
		return false;
	}

	_status = true;
	return true;
}

bool Server::stop() {
	if (!_status) return false;

	if (!_consumer->stop()) {
		return false;
	}

	_status = false;
	return true;
}

void Server::_process(int socket_in) {
	Request request(socket_in);
	Response response(socket_in);

	if (!request.valid()) {
		/* response.sendError(Protocol::Codes(Protocol::Code::BAD_REQUEST), "Invalid request."); */
		return;
	}

	std::string path = request.getPath();
	Protocol::Item method = request.getMethod();

	Server::Route route;
	if (!getRoute(path, method, route)) {
		/* response.sendError(Protocol::Codes(Protocol::Code::FORBIDDEN), "Path invalid/not found."); */
		return;
	}

	route.callback(&request, &response);

	if (!response.sent()) {
		/* response.sendError(Protocol::Codes(Protocol::Code::SERVICE_UNAVAILABLE), "Resource was not found or can't respond now."); */
	}

	return;
}