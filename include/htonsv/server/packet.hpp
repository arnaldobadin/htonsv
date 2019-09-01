#ifndef PACKET_HPP
#define PACKET_HPP

#include "htonsv/json/json.hpp"
#include "htonsv/server/protocol.hpp"

using json = nlohmann::json;

class Struct {
	public:
		struct Attributes {
			const std::string version = "HTTP/1.1";

			std::string path;
			Protocol::Item method;
			Protocol::Item code;
			std::unordered_map<std::string, std::string> headers;
			json body;

			Attributes() {
				code = Protocol::Codes(Protocol::Code::INTERNAL_SERVER_ERROR);
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