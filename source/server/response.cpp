#include "htonsv/server/response.h"

Htonsv::Response::Response(int socket_in) :
	_socket(socket_in),
	_sent(false)
{
	_packet.code = Htonsv::Protocol::Codes(Htonsv::Protocol::Code::OK);
	_packet.body = json::value_t::object;
}

Htonsv::Response::~Response() {
	
}

bool Htonsv::Response::sent() const {
	return _sent;
}

bool Htonsv::Response::code(Htonsv::Protocol::Code code) {
	Htonsv::Protocol::Item item = Htonsv::Protocol::Codes(code);
	if (item.id < 1) return false;
	_packet.code = item;
	return true;
}

bool Htonsv::Response::header(const std::string& key, const std::string& value) {
	if (!(key.length() && value.length())) return false;
	_packet.headers[key] = value;
	return true;
}

bool Htonsv::Response::body(const json& body) {
	_packet.body = body;
	return true;
}

void Htonsv::Response::clear() {
	_packet = {};
}

bool Htonsv::Response::error(Htonsv::Protocol::Code code) {
	clear();

	if (!this->code(code)) return false;

	json body = {{"status", false}};
	body["error"] = {};
	body["error"]["code"] = _packet.code.id;

	if (!this->body(body)) return false;
	return _send();
}

bool Htonsv::Response::error(Htonsv::Protocol::Code code, const std::string& message) {
	clear();

	if (!this->code(code)) return false;

	json body = {{"status", false}};
	body["error"] = {};
	body["error"]["code"] = _packet.code.id;
	body["error"]["message"] = message;

	if (!this->body(body)) return false;
	return _send();
}

bool Htonsv::Response::send() {
	return _send();
}

bool Htonsv::Response::send(const json& body) {
	_packet.body = body;
	return _send();
}

bool Htonsv::Response::_send() {
	header("Content-Type", "application/json");
	header("Connection", "Closed");

	std::string payload = _packet.out();

	if (write(_socket, payload.c_str(), payload.size()) < 1) {
		return false;
	}

	_sent = true;
	return true;
}