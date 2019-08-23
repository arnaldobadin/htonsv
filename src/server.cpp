#include "server.h"

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

	if (!request.isValid()) {
		response.sendError(Status::BadRequest, "Invalid request.");
		return;
	}

	std::string path = request.getPath();
	Struct::Methods method = request.getMethod();

	Server::Route route;
	if (!getRoute(path, method, route)) {
		response.sendError(Status::Forbidden, "Path invalid/not found.");
		return;
	}

	route.callback(&request, &response);

	if (!response.wasSent()) {
		response.sendError(Status::ServiceUnavailable, "Resource was not found or can't respond now.");
	}

	return;
}