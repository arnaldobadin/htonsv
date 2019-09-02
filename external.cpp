#include <htonsv/htonsv.hpp>

void getStatus(Request* request, Response* response) {
	std::cout << "Requesting status." << std::endl;

	json body = {
		{"hellou", 10}
	};

	response->body(body);
	response->code(Protocol::Code::OK);
	response->send();
}

int main(int argc, char* argv[]) {
	uint16_t port = 3636;
	Server server(port);
	
	server.route("/status", Protocol::Method::GET, getStatus);
	server.start();

	std::cout << "Server is running with success at port " << port << "." << std::endl;

	while (true) {}
	return 1;
}