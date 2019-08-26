#!/bin/bash

g++ \
	-L ../cmake/build/ \
		../cmake/build/server.lib \
	-I ./ \
		./simple-server.cpp \
 	-static
-o application.exe