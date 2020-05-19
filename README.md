## Simple HTTP JSON Server

### Setup:

```bash
mkdir build && cd build
cmake ..
sudo make install
```

### Usage:

Including:
```cpp
#include <htonsv/htonsv.hpp>
```

Setting up server:
```cpp
uint16_t port = 5000;

/* declare Server instance */
Htonsv::Server server(port);

/* set a route (entry) */
server.route("/status", Htonsv::Protocol::Method::GET, sendStatus);
server.route("/something", Htonsv::Protocol::Method::POST, doSomething);

/* start server */
server.start();

/* block current thread */
std::cin.get();
```

You can add routes, taking the path, method and function to be execute:
```cpp
/* you must to declare the functions */

void sendStatus(Htonsv::Request& request, Htonsv::Response& response) {
	/* create a JSON object that will be sent in response */
	json payload;
	payload["message"] = "Server is running without a problem.";

	/* set data to send on response */
	response.body(payload);
	/* unique call */
	response.send();
}

void doSomething(Htonsv::Request& request, Htonsv::Response& response) {
	/* get request input (user's input) -- coming as JSON object -- */
	json data = request.body();

	/* check field that came from request's payload */
	if (!data["field"]) {
		/* send error */
		response.error(Htonsv::Protocol::Code::BAD_REQUEST, "Missing some field.");
		return;
	}

	/* set data to send on response -- just mirroing -- */
	response.body(data);
	response.code(Protocol::Code::OK);
	/* unique call */
	response.send();
}

/* set routes (entries) */
server.route("/status", Htonsv::Protocol::Method::GET, sendStatus);
server.route("/something", Htonsv::Protocol::Method::POST, doSomething);
```

### Example:

```cpp
#include <htonsv/htonsv.hpp>

void getStatus(Htonsv::Request& request, Htonsv::Response& response) {
	json payload = {
		{"status", true},
		{"message", "Everything is fine."}
	};

	/* response.body(payload); or just */
	response.send(payload);
}

int main(int argc, char* argv[]) {
	uint16_t port = 7777;
	if (argc > 1) port = atoi(argv[1]);

	Htonsv::Server server(port);
	
	server.route("/status", Htonsv::Protocol::Method::GET, getStatus);
	server.start();

	std::cout << "Server is running with success at port " << port << "." << std::endl;

	std::cin.get();
	return 1;
}
```
