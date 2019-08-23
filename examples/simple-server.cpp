#include "external.hpp"

void sendStatus(Request* request, Response* response) {
	json payload;
	payload["message"] = "Everything is working smoothly as possible.";

	response->setBody(payload);
	response->sendSuccess();
}

void mirrorData(Request* request, Response* response) {
	json data = request->getBody();

	response->setBody(data);
	response->sendSuccess();
}

void blockThread(Request* request, Response* response) {
	while (true) {}
}

int main(int argc, char* argv[]) {
	int16_t port = 5000;

	std::unique_ptr<Server> server(new Server(port));

	server->setRoute("/status", Protocol::Method("GET"), sendStatus);
	server->setRoute("/mirror", Protocol::Method("POST"), mirrorData);
	server->setRoute("/block", Protocol::Method("GET"), blockThread);

	server->start();

	while (true) {}

	return 1;
}