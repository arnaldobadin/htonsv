#include "external.hpp"

int main() {
	Server* server = new Server(1111);
	delete server;
	return 1;
}