#include "htonsv/server/response.h"

Response::Response(int socket_in) :
	_socket(socket_in),
	_sent(false)
{
	_packet.code = Protocol::Codes(Protocol::Code::NOT_FOUND);
	_packet.body = json::value_t::object;
}

Response::~Response() {
	
}

bool Response::sent() const {
	return _sent;
}

bool Response::code(Protocol::Code code) {
	Protocol::Item item = Protocol::Codes(code);
	if (item.id < 1) return false;
	_packet.code = item;
	return true;
}

bool Response::header(const std::string& key, const std::string& value) {
	if (!(key.length() && value.length())) return false;
	_packet.headers[key] = value;
	return true;
}

bool Response::body(const json& body) {
	_packet.body = body;
	return true;
}

void Response::clear() {
	_packet = {};
}

bool Response::error(Protocol::Code code, const std::string& message) {
	clear();

	if (!this->code(code)) return false;

	json body = {{"status", false}};
	body["error"] = {};
	body["error"]["code"] = _packet.code.id;
	body["error"]["message"] = message;

	if (!this->body(body)) return false;
	return _send();
}

bool Response::send() {
	return _send();
}

bool Response::send(const json& body) {
	_packet.body = body;
	return _send();
}

bool Response::_send() {
	header("Server", "Dark");
	header("Content-Type", "application/json");
	header("Connection", "Closed");

	std::string payload = _packet.out();

	std::cout << payload << std::endl;

	if (write(_socket, payload.c_str(), payload.size()) < 1) {
		return false;
	}

	_sent = true;
	return true;
}