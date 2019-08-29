#ifndef LISTENER_H
#define LISTENER_H

#include <cstdint>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdexcept>
#include <atomic>

class Listener {
	public:
		Listener(int16_t port, unsigned int max_connection_count = 512);
		~Listener();

		bool start();
		bool stop();

		int acquire();

	private:
		int16_t _port;
		unsigned int _max_connection_count;

		std::atomic<bool> _status;

		int _socket;
		struct sockaddr_in _address;

		bool _create();
		bool _bind();
};

#endif