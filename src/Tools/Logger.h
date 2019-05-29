#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

class Logger {
	public:
		enum class TYPES {
			ERROR = 0x0,
			NONE = 0x01,
			SUCCESS = 0x02,
			WARNING = 0x04,
			INFO = 0x08
		};

		static void doSendMessage(TYPES type, const std::string& message) {
			std::string status;

			if (type == TYPES::ERROR) status = "Error";
			else if (type == TYPES::NONE) status = "Unknown";
			else if (type == TYPES::SUCCESS) status = "Success";
			else if (type == TYPES::WARNING) status = "Warning";
			else if (type == TYPES::INFO) status = "Info";

			std::cout << "[" << status << "] " << message << std::endl;

			if (type == TYPES::ERROR) throw;
		}

	private:

};

#endif