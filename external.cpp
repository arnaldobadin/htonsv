#include <htonsv/htonsv.hpp>

void getStatus(Htonsv::Request& request, Htonsv::Response& response) {
	json payload = {
		{"status", true},
		{"message", "Everything is fine."}
	};

	response.send(payload);
}

int main(int argc, char* argv[]) {
	uint16_t port = 7777;
	if (argc > 1) port = atoi(argv[1]);

	Htonsv::Server server(port);
	
	server.route("/status", Htonsv::Protocol::Method::GET, getStatus);
	server.start();

	std::cout << "Server is running with success at port " << port << "." << std::endl;
	std::cout << "Hit any key to close it." << std::endl;

	std::cin.get();
	std::cout << "Server closed with success." << std::endl;
	return 1;
}