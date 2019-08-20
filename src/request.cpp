#include "request.h"

Request::Request(int socket, unsigned int buffer_size) : 
	_socket(socket),
	_buffer_size(buffer_size),
	_status(false)
{
	_data = _receiveData(_socket);
	if (!_data.length()) return;

	bool result;
	result = _parseData(_data, _attributes);

	if (!result) return;
	if (!_attributes.isValidRequest()) return;

	_status = true;
}

Request::~Request() {

}

bool Request::isValid() const {
	return _status;
}

std::string Request::_receiveData(int sock_in) {
	std::vector<char> buffer(_buffer_size);
	read(sock_in, buffer.data(), buffer.size());
	return std::string(buffer.data(), buffer.size());
}

bool Request::_parseData(const std::string& data, Struct::Attributes& attributes) {
	std::string delimiter = "\r\n";
	std::vector<std::string> rows = _splitText(data, delimiter);
	if (!rows.size()) return false;

	std::string header = rows[0];
	rows.erase(rows.begin());

	if (!header.length()) return false;

	std::vector<std::string> parsed_header = _splitText(header, std::string(" "));
	if (parsed_header.size() < 2) return false;

	Struct::Methods method = Struct::parseMethod(parsed_header[0]);
	if (method == Struct::Methods::NONE) return false;

	std::string path = parsed_header[1];

	std::unordered_map<std::string, std::string> headers;
	for (size_t i = 0; i < rows.size(); i++) {
		std::string row = rows[i];
		delimiter = ":";

		std::vector<std::string> splited = _splitText(row, delimiter);
		if (splited.size() != 2) continue;

		headers[splited[0]] = splited[1];
	}

	attributes.method = method;
	attributes.path = path;
	attributes.headers = headers;
    attributes.body = json::value_t::object;

    int data_length = strlen(data.c_str());

	std::string content_length = headers["Content-Length"];
 	int content_size = atoi(content_length.c_str());
    if (!content_size) return false;

    std::string body = data.substr(data_length - content_size, data_length);
    json parsed = json::parse(body, nullptr, false);
    if (parsed == NULL || parsed.is_discarded()) return true;

    attributes.body = parsed;
    return true;
}

std::vector<std::string> Request::_splitText(const std::string& text, const std::string& delimiter) {
    std::vector<std::string> result;
    unsigned int delimiter_length = delimiter.length();

    if (!text.length()) return result;
    
    std::string block;
    std::string region;
    int index = 0;

    for (size_t i = 0; i < text.length(); i++) {
        block = text.substr(i, delimiter_length);
        if (block.length() != delimiter_length) continue;
        
        if (block == delimiter) {
            region = text.substr(index, i - index);
            result.push_back(region);
            index = i + delimiter_length;
        }
    }

    if (!result.size()) {
    	result.push_back(text);
    	return result;
    }

    std::string tail = text.substr(index, delimiter_length - index);
    if (tail.length()) result.push_back(tail);

    return result;
}

