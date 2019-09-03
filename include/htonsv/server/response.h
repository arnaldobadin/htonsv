#ifndef RESPONSE_H
#define RESPONSE_H

#include <unistd.h>
#include <iostream>
#include <string>
#include <unordered_map>

#include "htonsv/server/packet.hpp"

class Response {
	public:
		Response(int socket_in);
		~Response();

		bool sent() const;

		bool code(Protocol::Code code);
		bool header(const std::string& key, const std::string& value);
		bool body(const json& body);

		void clear();
		bool error(Protocol::Code code);
		bool error(Protocol::Code code, const std::string& message);
		bool send();
		bool send(const json& body);

	private:
		int _socket;

		bool _sent;
		Packet::Item _packet;

		bool _send();
};

#endif