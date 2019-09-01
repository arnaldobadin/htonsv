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

	private:
		int _socket;

		bool _sent;

		Packet::Item _packet;

		bool _send();
};

#endif