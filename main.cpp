#include "Server/Server.h"

void exec(Request* request, Response* response) {
    json body;

    body["foo"] = 123;
    body["bar"] = true;

    response->setBody(body);
    response->doSendSuccess();
}

int main(int argc, char* argv[]) {
    Server* server = new Server(5000);

    server->setRoute("/getStatus", Struct::Methods::GET, exec);
    server->setRoute("/postStatus", Struct::Methods::POST, exec);
    server->doListen();

    delete server;
    return 1;
}