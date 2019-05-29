#ifndef LISTENER_H
#define LISTENER_H

#include <cstdint>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "Tools/Logger.h"

class Listener {
	public:
		Listener(int16_t port);
		~Listener();

		int doAccept();
		int doListen(unsigned int max_connections);
		bool doStop();

	private:
		int16_t _port;

		int _socket;
		struct sockaddr_in _address;

		bool _status;

		bool _doCreateSocket(int& socket_in);
		bool _doBindSocket(int socket_in);
};

#endif