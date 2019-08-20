#ifndef LISTENER_H
#define LISTENER_H

#include <cstdint>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdexcept>

class Listener {
	public:
		Listener(int16_t port);
		~Listener();

		bool start(unsigned int max_connections);
		bool stop();
		int acquire();

	private:
		int16_t _port;

		int _socket;
		struct sockaddr_in _address;

		bool _status;
		bool _listen;

		bool _createSocket(int& socket_in);
		bool _bindSocket(int socket_in);
};

#endif