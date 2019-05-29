#ifndef RESPONSE_H
#define RESPONSE_H

#include <unistd.h>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Server/Struct.h"

class Response {
	public:
		Response(int socket_in);
		~Response();

		bool isSent() const {return _sent;}
		void setCode(HttpStatus::Code code) {_attributes.code = code;}
		void setHeader(std::string key, std::string value) {_attributes.headers[key] = value;}
		void setBody(json body) {_attributes.body = body;}
		void doClearHeaders() {_attributes.headers.clear();}
		void doClearBody() {_attributes.body = json::value_t::object;}

		bool doSendSuccess();
		bool doSendError(HttpStatus::Code code, const std::string& message);

	private:
		int _socket;
		bool _sent;

		Struct::Attributes _attributes;

		bool _doSendPayload();
		bool _doCreatePayload(std::string& payload);
};

#endif