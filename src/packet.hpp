#ifndef PACKET_H
#define PACKET_H

#include <json.hpp>

#include "protocol.hpp"

using json = nlohmann::json;

class Struct {
	public:
		struct Attributes {
			const std::string version = "HTTP/1.1";

			std::string path;
			Protocol::Table::Item method;
			Protocol::Table::Item code;
			std::unordered_map<std::string, std::string> headers;
			json body;

			Attributes() {
				code = Protocol::Status("InternalServerError");
				body = json::value_t::object;
			}

			bool isValidRequest() const {
				if (!path.length()) return false;
				if (method.id < 1) return false;
				if (!headers.size()) return false;
				return true;
			}

			bool isValidResponse() const {
				if (!headers.size()) return false;
				return true;	
			}
		};
		
	private:
};

#endif