#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>
#include <unordered_map>

#include "htonsv/json/json.hpp"
#include "htonsv/server/text.hpp"
#include "htonsv/server/protocol.hpp"

using json = nlohmann::json;

namespace Packet {
	struct Item {
		std::string path;

		Protocol::Item method;
		Protocol::Item code;

		std::unordered_map<std::string, std::string> headers;
		json body;

		bool in(const std::string& data);
		std::string out();
	};

	inline bool Item::in(const std::string& data) {
		std::string delimiter = "\r\n";
		std::vector<std::string> rows = Text::split(data, delimiter);
		if (!rows.size()) return false;

		std::string header = rows[0];
		rows.erase(rows.begin());

		if (!header.length()) return false;

		std::vector<std::string> parsed_header = Text::split(header, std::string(" "));
		if (parsed_header.size() < 2) return false;

		Protocol::Item method = Protocol::Methods(parsed_header[0]);
		if (method.id < 1) return false;

		std::string path = parsed_header[1];

		std::unordered_map<std::string, std::string> headers;
		for (size_t i = 0; i < rows.size(); i++) {
			std::string row = rows[i];
			delimiter = ":";

			std::vector<std::string> splited = Text::split(row, delimiter);
			if (splited.size() != 2) continue;

			headers[splited[0]] = splited[1];
		}

		this->path = path;
		this->method = method;
		this->headers = headers;
		this->body = json::value_t::object;

		int data_length = strlen(data.c_str());

		std::string content_length = headers["Content-Length"];
		int content_size = atoi(content_length.c_str());
		if (!content_size) return true;

		std::string body = data.substr(data_length - content_size, data_length);
		json parsed = json::parse(body, nullptr, false);
		if (parsed == NULL || parsed.is_discarded()) return true;

		this->body = parsed;
		return true;
	}

	inline std::string Item::out() {
		std::string payload;
		std::string data = this->body.dump(4);

		int data_length = data.size();

		if (data_length) {
			this->headers["Content-Length"] = std::to_string(data_length);
		}

		payload += Protocol::HTTP_VERSION + " " + std::to_string(this->code.id) + " " + this->code.name + "\r\n";

		std::unordered_map<std::string, std::string>::iterator iterator;
		for (iterator = this->headers.begin(); iterator != this->headers.end(); iterator++) {
		    std::string key = iterator->first;
		    std::string value = iterator->second;

		    payload += key + ": " + value + "\r\n";
		}

		if (data_length) payload += "\r\n" + data + "\r\n\r\n";

		return payload;
	}
};

#endif