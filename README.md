# Simple HTTP JSON Server

Just a simple HTTP JSON Server;

### Usage:

> Requiring:
```cpp
	#include "external.hpp"
```

> Setting up server:
```cpp
	int port = 5000;

	/* declare Server instance */
	Server server(port);

	/* set a route (entry) */
	server.setRoute("/status", Struct::Methods::GET, sendStatus);

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
		response->setBody(payload);
		/* unique call */
		response->sendSuccess();
	}

	void doSomething(Request* request, Response* response) {
		/* get request input (user's input) -- coming as JSON object -- */
		json data = request->getBody();

		/* set data to send on response -- just mirroing -- */
		response->setBody(data);
		/* unique call */
		response->sendSuccess();
	}

	/* set routes (entries) */
	server.setRoute("/status", Struct::Methods::GET, sendStatus);
	server.setRoute("/status", Struct::Methods::POST, doSomething);
```

> 

### Example:

> See examples folder:
```cpp
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
```

### Todo:

- [ ] Make it cross-platform;
- [ ] Add cmake;
- [ ] Review _processRequest (Server);
- [ ] Review todo;
- [ ] Add this to all class members [should i?];
- [ ] Review Request and Response;
- [ ] Think another way to handle PAYLOADS (sendSuccess, etc);
- [ ] Think a better way to store Requests and Response's attr;
- [ ] Fix "status.h";
- [ ] Fix "struct.h";
- [ ] Add portable version;
- [ ] Test framework;
- [ ] Pass compiled tags "pendantic";
- [ ] Update documentation;
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
