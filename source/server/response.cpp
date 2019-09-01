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

bool Response::_send() {
	std::string payload = _packet.out();

	if (write(_socket, payload.c_str(), payload.size()) < 1) {
		return false;
	}

	return true;
}