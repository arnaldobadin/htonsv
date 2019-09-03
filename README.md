# Simple HTTP JSON Server

Just a simple HTTP JSON Server;

### Setup:

```bash
mkdir build && cd build
cmake ..
sudo make install
```

### Usage:

> Including:
```cpp
#include <htonsv/htonsv.hpp>
```

> Setting up server:
```cpp
uint16_t port = 5000;

/* declare Server instance */
Server server(port);

/* set a route (entry) */
server.route("/status", Protocol::Method::GET, sendStatus);
server.route("/something", Protocol::Method::POST, doSomething);

/* start server */
server.start();

/* block current thread */
while (true) {}
```

> You can add routes, taking the path, method and function to be execute:
```cpp
/* you must to declare the functions */

void sendStatus(Request* request, Response* response) {
	/* create a JSON object that will be sent in response */
	json payload;
	payload["message"] = "Server is running without a problem.";

	/* set data to send on response */
	response->body(payload);
	/* unique call */
	response->send();
}

void doSomething(Request* request, Response* response) {
	/* get request input (user's input) -- coming as JSON object -- */
	json data = request->body();

	/* check field that came from request's payload */
	if (!data["field"]) {
		/* send error */
		response->error(Protocol::Code::BAD_REQUEST, "Missing some field.");
		return;
	}

	/* set data to send on response -- just mirroing -- */
	response->body(data);
	response->code(Protocol::Code::OK);
	/* unique call */
	response->send();
}

/* set routes (entries) */
server.route("/status", Protocol::Method::GET, sendStatus);
server.route("/something", Protocol::Method::POST, doSomething);
```

> 

### Example:

```cpp
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
```

### Todo:

- [ ] Fix head->>tail<< in requests, extend lifetime and keep connection alive until TIMEOUT or specific shutdown;
- [ ] Make it cross-platform;
- [ ] Check cmake pthread compile needs;
- [ ] Review todo;
- [ ] Add "this" to all class members [should i?];
- [ ] Add portable version;
- [ ] Test framework;
- [ ] Pass compiled tags "pendantic";
- [ ] Upgrade documentation (make it fancy);
- [x] Update documentation;
- [x] Review Request and Response;
- [x] Review _processRequest (Server);
- [x] Think another way to handle PAYLOADS (sendSuccess, etc);
- [x] Think a better way to store Requests and Response's attr;
- [x] Remake response.h -- missing functions and functionality --;
- [x] Make Req/Res pointers i guess -- look for overhead heap vs stack in runtime -- */
- [x] Fix transferred a partial file "Response.h";
- [x] Fix "struct.h";
- [x] Add cmake;
- [x] Fix "status.h" -- now is protocol.hpp --;
- [x] Set all _status to atomic;
- [x] Change listener and server triggers;
- [x] Add a new class (consumer) and remake server;
- [x] Fix lambda function into server > consumer creation [changed to std::mem_fn, than i regret and use lambda again];
- [x] Move splitText to another section;
- [x] Analyze if changing vector to queue will be better in performance (i think yes) in _queue on server.h [queue won];
- [x] Update (create one '-') documentation;
- [x] ~~Make dynamic listener threads that escalate as requests are coming~~ instead of doing that i'm listing the threads cpu capacity and using them as _thread_count;
- [x] Add lock to _listen bool attr;
- [x] Must fix block string function;
- [x] Modify extension connection;

*this repo is currently active and is my main purpose until I finish it*
