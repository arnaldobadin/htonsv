#ifndef CONSUMER_H
#define CONSUMER_H

#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include <functional>

#include "server/listener.h"

class Consumer {
	public:
		Consumer(std::uint16_t port, std::function<void(int)> callback);
		~Consumer();

		static const unsigned int THREAD_COUNT_DEFAULT = 5;
		static const unsigned int MAX_CONNECTION_COUNT_DEFAULT = 512;

		bool start();
		bool stop();

	private:
		std::uint16_t _port;
		int _socket;
		
		std::atomic<bool> _status;

		unsigned int _thread_count;
		unsigned int _max_connection_count;

		std::atomic<bool> _signal;

		std::mutex _mutex;
		std::condition_variable _condition;

		std::thread _thread_consume;
		std::vector<std::thread> _threads_process;

		std::unique_ptr<Listener> _listener;
		std::queue<unsigned int> _queue;
		std::function<void(int)> _callback;

		void _consume(const std::string& name);
		void _process(const std::string& name);
};

#endif