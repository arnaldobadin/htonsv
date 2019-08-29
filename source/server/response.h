#ifndef RESPONSE_H
#define RESPONSE_H

#include <unistd.h>
#include <iostream>
#include <string>
#include <unordered_map>

#include "server/packet.hpp"

class Response {
	public:
		Response(int socket_in);
		~Response();

		bool wasSent() const {return _sent;}
		void setCode(Protocol::Table::Item code) {_attributes.code = code;}
		void setHeader(std::string key, std::string value) {_attributes.headers[key] = value;}
		void setBody(json body) {_attributes.body = body;}
		void clearHeaders() {_attributes.headers.clear();}
		void clearBody() {_attributes.body = json::value_t::object;}

		bool sendSuccess();
		bool sendError(Protocol::Table::Item code, const std::string& message);

	private:
		int _socket;
		bool _sent;

		Struct::Attributes _attributes;

		bool _sendPayload();
		bool _createPayload(std::string& payload);
};

#endif