#!/bin/bash

#sudo g++ -W -Wall -Werror -Wextra -pedantic -O2 \
sudo g++ \
	-I ./ \
		external.hpp \
	-I lib \
		./lib/json.hpp \
	-I src \
		./src/server.h ./src/server.cpp \
		./src/listener.h ./src/listener.cpp \
		./src/request.h ./src/request.cpp \
		./src/response.h ./src/response.cpp \
		./src/struct.h \
		./src/status.h \
	-I examples \
		./examples/simple-server.cpp \
	-pthread \
-o application.exe

sudo find . -type f -name '*.gch' -delete
sudo ./application.exe