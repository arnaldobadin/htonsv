#!/bin/bash

echo "[>] Started compiling application;"

#sudo g++ -W -Wall -Werror -Wextra -pedantic -O2 \
sudo g++ \
	-I ./ \
		external.hpp \
	-I lib \
		./lib/json.hpp \
	-I src \
		./src/server.h ./src/server.cpp \
		./src/listener.h ./src/listener.cpp \
		./src/consumer.h ./src/consumer.cpp \
		./src/request.h ./src/request.cpp \
		./src/response.h ./src/response.cpp \
		./src/struct.hpp \
		./src/status.hpp \
		./src/text.hpp \
	-I examples \
		./examples/simple-server.cpp \
	-pthread \
-o application.exe

sudo find . -type f -name '*.gch' -delete

echo "[x] Finished compiling application;"

echo "[>] Running application;"

sudo ./application.exe

echo "[x] Closing application;"