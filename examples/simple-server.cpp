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

int main(int argc, char* argv[]) {
    int16_t port = 5000;

    std::unique_ptr<Server> server(new Server(port));

    server->setRoute("/status", Struct::Methods::GET, sendStatus);
    server->setRoute("/mirror", Struct::Methods::POST, mirrorData);

    server->start();

    while (true) {}

    return 1;
}