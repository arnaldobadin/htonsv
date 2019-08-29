#ifndef REQUEST_H
#define REQUEST_H

#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

#include "json/json.hpp"
#include "server/packet.hpp"
#include "server/text.hpp"

using json = nlohmann::json;

class Request {
	public:
		Request(int socket, unsigned int buffer_size = 1024);
		~Request();

		bool isValid() const;
		std::string getPath() const {return _attributes.path;}
		Protocol::Table::Item getMethod() const {return _attributes.method;}
		const std::unordered_map<std::string, std::string>& getHeaders() const {return _attributes.headers;}
		const std::string& getHeader(const std::string& header) {return _attributes.headers[header];}
		const json& getBody() const {return _attributes.body;}

	private:
		int _socket;
		unsigned int _buffer_size;
		std::string _data;
		Struct::Attributes _attributes;
		bool _status;

		std::string _receiveData(int sock_in);
		bool _parseData(const std::string& data, Struct::Attributes& attributes);
};

#endif