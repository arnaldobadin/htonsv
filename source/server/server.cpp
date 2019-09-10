#include "htonsv/server/server.h"

Htonsv::Server::Server(std::uint16_t port) : 
    _port(port),
    _status(false)
{
	_consumer = std::unique_ptr<Consumer>(
		new Consumer(_port, [this] (int socket_in) {this->_process(socket_in);})
	);
}

Htonsv::Server::~Server() {
	stop();
}

bool Htonsv::Server::start() {
	if (_status) return false;

	if (!_consumer->start()) {
		return false;
	}

	_status = true;
	return true;
}

bool Htonsv::Server::stop() {
	if (!_status) return false;

	if (!_consumer->stop()) {
		return false;
	}

	_status = false;
	return true;
}

bool Htonsv::Server::route(const std::string& path, Protocol::Method method, std::function<void(Request&, Response&)> callback) {
	Protocol::Item item = Protocol::Methods(method);
	return _setRoute(path, item, callback);
}

bool Htonsv::Server::_setRoute(const std::string& path, Protocol::Item method, std::function<void(Request&, Response&)> callback) {
	for (const Route& value : _routes) {
		if (value.path == path && value.method.id == method.id) {
			return false;
		}
	}

	Htonsv::Server::Route route = {path, method, callback};
	if (!route.valid()) return false;

	_routes.push_back(route);
	return true;
}

bool Htonsv::Server::_getRoute(const std::string& path, Protocol::Item method, Htonsv::Server::Route& route) {
	for (const Route& value : _routes) {
		if (value.path == path && value.method.id == method.id) {
			route = value;
			return true;
		}
	}
    return false;
}

void Htonsv::Server::_process(int socket_in) {
	Request request(socket_in);
	Response response(socket_in);

	if (!(request.load() && request.valid())) {
		response.error(Protocol::Code::BAD_REQUEST, "Invalid request.");
		return;
	}

	std::string path = request.path();
	Protocol::Item method = request.method();

	Htonsv::Server::Route route;
	if (!_getRoute(path, method, route)) {
		response.error(Protocol::Code::NOT_FOUND, "Path or/and method invalid/not found.");
		return;
	}

	route.callback(request, response);

	if (!response.sent()) {
		response.error(Protocol::Code::SERVICE_UNAVAILABLE,
			"Service/resource was not found or can't respond now."
		);
	}

	return;
}