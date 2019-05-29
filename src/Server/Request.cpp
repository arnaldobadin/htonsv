#include "Server/Request.h"

Request::Request(int socket, unsigned int buffer_size) : 
	_socket(socket),
	_buffer_size(buffer_size),
	_status(false)
{
	_data = _doReceiveData(_socket);
	if (!_data.length()) return;

	bool result;
	result = _doParseData(_data, _attributes);

	if (!result) return;
	if (!_attributes.isValidRequest()) return;

	_status = true;
}

Request::~Request() {

}

bool Request::isValid() const {
	return _status;
}

std::string Request::_doReceiveData(int sock_in) {
	std::vector<char> buffer(_buffer_size);
	read(sock_in, buffer.data(), buffer.size());
	return std::string(buffer.data(), buffer.size());
}

bool Request::_doParseData(const std::string& data, Struct::Attributes& attributes) {
	std::string delimiter = "\r\n";
	std::vector<std::string> rows = _doSplitText(data, delimiter);
	if (!rows.size()) return false;

	std::string header = rows[0];
	rows.erase(rows.begin());

	if (!header.length()) return false;

	std::vector<std::string> parsed_header = _doSplitText(header, std::string(" "));
	if (parsed_header.size() < 2) return false;

	Struct::Methods method = Struct::doParseMethod(parsed_header[0]);
	if (method == Struct::Methods::NONE) return false;

	std::string path = parsed_header[1];

	std::unordered_map<std::string, std::string> headers;
	for (size_t i = 0; i < rows.size(); i++) {
		std::string row = rows[i];
		delimiter = ":";

		std::vector<std::string> splited = _doSplitText(row, delimiter, true);
		if (splited.size() != 2) continue;

		headers[splited[0]] = splited[1];
	}

	attributes.method = method;
	attributes.path = path;
	attributes.headers = headers;

	std::string content_length = headers["Content-Length"];
	int content_size = 0;

	if (content_size == atoi(content_length.c_str())) {
		std::string body = data.substr(data.length() - content_size, data.length());
		json parsed_body = json::parse(body, nullptr, false);
		if (parsed_body != NULL && !parsed_body.is_discarded()) attributes.body = parsed_body;
	}

	return true;
}

std::vector<std::string> Request::_doSplitText(const std::string& text, const std::string& delimiter) {
    std::vector<std::string> result;
    unsigned int delimiter_length = delimiter.length();
    
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

    return result;
}

std::vector<std::string> Request::_doSplitText(const std::string& text, const std::string& delimiter, int lock) {
	if (!lock) return Request::_doSplitText(text, delimiter);

    std::vector<std::string> result;
    unsigned int delimiter_length = delimiter.length();
    
    std::string block;
    std::string region;

    for (size_t i = 0; i < text.length(); i++) {
        block = text.substr(i, delimiter_length);
        if (block.length() != delimiter_length) continue;
        
        if (block == delimiter) {
            region = text.substr(0, i);
            region = std::regex_replace(region, std::regex("^ +| +$|( ) +"), "$1");
            if (region.length()) result.push_back(region);

            region = text.substr(i + delimiter_length, text.length());
            region = std::regex_replace(region, std::regex("^ +| +$|( ) +"), "$1");
            if (region.length()) result.push_back(region);
            return result;
        }
    }

    return result;
}

