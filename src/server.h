#ifndef SERVER_H
#define SERVER_H

#include <cstdint>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <stdexcept>

#include "listener.h"
#include "request.h"
#include "response.h"
#include "struct.h"

class Server {
	public:
		Server(std::uint16_t port, unsigned int max_connections = 64, unsigned int thread_count = 5);
		~Server();

		struct Route {
			std::string path;
			Struct::Methods method;
			std::function<void (Request*, Response*)> callback;

			bool isValid() {
				if (!path.length()) return false;
				if (method < Struct::Methods::FIRST || method > Struct::Methods::LAST) return false;
				if (callback == nullptr) return false;
				return true;
			}
		};

		bool setRoute(const std::string& path, Struct::Methods method, std::function<void(Request*, Response*)> callback);
		bool getRoute(const std::string& path, Struct::Methods method, Route& route);

		bool start();
		bool stop();

	private:
		std::uint16_t _port;
		unsigned int _max_connections;
		unsigned int _thread_count;

		std::mutex _mutex;
		std::condition_variable _condition;

		bool _signal;
		bool _listen;

		std::vector<unsigned int> _queue;
		std::vector<Route> _routes;

		std::thread _thread_consume;
		std::vector<std::thread> _thread_process;

		std::unique_ptr<Listener> _listener;

		void _consumeSocket();
		void _processSocket();
		bool _processRequest(Request* request, Response* response);
};

#endif