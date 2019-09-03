#include <htonsv/htonsv.hpp>

void getStatus(Request* request, Response* response) {
	json payload = {
		{"status", true},
		{"message", "Everything is fine."}
	};

	/* response->body(payload); or just */
	response->send(payload);
}

int main(int argc, char* argv[]) {
	uint16_t port = 7777;
	if (argc > 1) port = atoi(argv[1]);

	Server server(port);
	
	server.route("/status", Protocol::Method::GET, getStatus);
	server.start();

	std::cout << "Server is running with success at port " << port << "." << std::endl;

	while (true) {}
	return 1;
}