#!/bin/bash

#sudo g++ \
sudo g++ -W -Wall -Werror -Wextra -pedantic -O2 \
	main.cpp \
	-I lib \
		./lib/json.hpp \
	-I src \
		./src/Server/Server.h ./src/Server/Server.cpp \
		./src/Server/Listener.h ./src/Server/Listener.cpp \
		./src/Server/Request.h ./src/Server/Request.cpp \
		./src/Server/Response.h ./src/Server/Response.cpp \
		./src/Server/Struct.h \
		./src/Server/Status.h \
		./src/Tools/Logger.h \
	-pthread \
-o main.exe

sudo ./main.exe