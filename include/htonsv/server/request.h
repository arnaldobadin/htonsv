#ifndef REQUEST_H
#define REQUEST_H

#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

#include "htonsv/server/packet.hpp"

using json = nlohmann::json;

namespace Htonsv {
	class Request;
}

class Htonsv::Request {
	public:
		Request(int socket, unsigned int buffer_size = 1024);
		~Request();

		static const unsigned int BUFFER_SIZE_DEFAULT = 1024;

		bool isValid() const;

		inline std::string path() const {return _packet.path;}
		inline Protocol::Item method() const {return _packet.method;}
		inline std::string header(const std::string& header) {return _packet.headers[header];}
		inline json body() const {return _packet.body;}

		bool valid() const;
		bool load();

	private:
		int _socket;
		unsigned int _buffer_size;

		bool _status;
		
		std::string _data;
		Packet::Item _packet;

		bool _receive();
		bool _transform();
};

#endif