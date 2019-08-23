#ifndef STRUCT_H
#define STRUCT_H

#include <json.hpp>

#include "status.hpp"

using json = nlohmann::json;

class Struct {
	public:
		enum class Methods {
			NONE = 0, GET = 1, POST = 2, FIRST = GET, LAST = POST
		};

		struct Attributes {
			const std::string version = "HTTP/1.1";

			std::string path;
			Methods method;
			Status::Code code;
			std::unordered_map<std::string, std::string> headers;
			json body;

			Attributes() {
				code = Status::InternalServerError;
				body = json::value_t::object;
			}

			bool isValidRequest() const {
				if (!path.length()) return false;
				if (method < Methods::FIRST || method > Methods::LAST) return false;
				if (!headers.size()) return false;
				return true;
			}

			bool isValidResponse() const {
				if (!headers.size()) return false;
				return true;	
			}
		};

		static Methods parseMethod(const std::string& value) {
			Methods target = Methods::NONE;

			if (value == "GET") target = Methods::GET;
			if (value == "POST") target = Methods::POST;

			return target;
		}
		
	private:
};

#endif