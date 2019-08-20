#include "response.h"

Response::Response(int socket_in) :
	_socket(socket_in),
	_sent(false)
{

}

Response::~Response() {
	
}

bool Response::sendSuccess() {
	setCode(HttpStatus::Code::OK);
	setHeader("Connection", "Closed");
	return _sendPayload();
}

bool Response::sendError(HttpStatus::Code code, const std::string& message) {
	setCode(code);
	clearHeaders();
	clearBody();

	setHeader("Connection", "Closed");

	json body;
	body["error"] = {};
	body["error"]["code"] = code;
	body["error"]["message"] = message;

	setBody(body);
	return _sendPayload();
}

bool Response::_sendPayload() {
	if (_sent) return false;

	setHeader("Server", "Dark");
	setHeader("Content-Type", "application/json");

	std::string payload;
	if (!_createPayload(payload)) {
		return false;
	}

	if (write(_socket, payload.c_str(), payload.size()) < 1) {
		return false;
	}

	_sent = true;
	return true;
}

bool Response::_createPayload(std::string& payload) {
	std::string current_payload;
    std::string data = _attributes.body.dump(4);

    int data_length = data.size();

	if (data_length) {
		_attributes.headers["Content-Length"] = std::to_string(data_length);
	}

	current_payload += _attributes.version + " " + std::to_string((int) _attributes.code) + " " + HttpStatus::getReasonPhrase(_attributes.code) + "\r\n";

    std::unordered_map<std::string, std::string>::iterator iterator;
    for (iterator = _attributes.headers.begin(); iterator != _attributes.headers.end(); iterator++) {
        std::string key = iterator->first;
        std::string value = iterator->second;

        current_payload += key + ": " + value + "\r\n";
    }

    if (data_length) current_payload += "\r\n" + data + "\r\n\r\n";

    payload = current_payload;
    return true;
}