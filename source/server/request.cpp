#include "htonsv/server/request.h"

Request::Request(int socket, unsigned int buffer_size) : 
	_socket(socket),
	_buffer_size(buffer_size),
	_status(false)
{
	if (_buffer_size < BUFFER_SIZE_DEFAULT) {
		_buffer_size = BUFFER_SIZE_DEFAULT;
	}
}

Request::~Request() {

}

bool Request::valid() const {
	return _status;
}

bool Request::load() {
	if (_status) return false;

	if (!(_receive() && _transform())) return false;
	return _status = true;
}

bool Request::_receive() {
	std::vector<char> buffer(_buffer_size);
	
	read(_socket, buffer.data(), buffer.size());

	_data = std::string(buffer.data(), buffer.size());

	if (!_data.length()) return false;
	return true;
}

bool Request::_transform() {
	if (!_data.length()) return false;
	return _packet.in(_data);
}