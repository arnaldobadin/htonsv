#ifndef REQUEST_H
#define REQUEST_H

#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <json.hpp>

#include "Server/Struct.h"

using json = nlohmann::json;

class Request {
	public:
		Request(int socket, unsigned int buffer_size = 1024);
		~Request();

		bool isValid() const;
		std::string getPath() const {return _attributes.path;}
		Struct::Methods getMethod() const {return _attributes.method;}
		const std::unordered_map<std::string, std::string>& getHeaders() const {return _attributes.headers;}
		const std::string& getHeader(const std::string& header) {return _attributes.headers[header];}
		const json& getBody() const {return _attributes.body;}

	private:
		int _socket;
		unsigned int _buffer_size;
		std::string _data;
		Struct::Attributes _attributes;
		bool _status;

		std::string _doReceiveData(int sock_in);
		bool _doParseData(const std::string& data, Struct::Attributes& attributes);
		std::vector<std::string> _doSplitText(const std::string& text, const std::string& delimiter);
		std::vector<std::string> _doSplitText(const std::string& text, const std::string& delimiter, int lock);
};

#endif