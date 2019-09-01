#ifndef SERVER_H
#define SERVER_H

#include <string.h>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <atomic>
#include <memory>

#include "htonsv/server/consumer.h"
#include "htonsv/server/request.h"
#include "htonsv/server/response.h"
#include "htonsv/server/packet.hpp"

class Server {
	public:
		Server(std::uint16_t port);
		~Server();

		struct Route {
			std::string path;
			Protocol::Item method;
			std::function<void (Request*, Response*)> callback;

			bool isValid() {
				if (!path.length()) return false;
				if (method.id < 1) return false;
				if (callback == nullptr) return false;
				return true;
			}
		};

		bool setRoute(const std::string& path, Protocol::Item method, std::function<void(Request*, Response*)> callback);
		bool getRoute(const std::string& path, Protocol::Item method, Route& route);

		bool start();
		bool stop();

	private:
		std::uint16_t _port;

		std::atomic<bool> _status;

		std::vector<Route> _routes;
		std::unique_ptr<Consumer> _consumer;

		void _process(int socket_in);
};

#endif