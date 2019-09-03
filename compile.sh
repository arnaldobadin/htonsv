#g++ -W -Wall -Werror -Wextra -pedantic -O2 \
g++ \
	-I ./include \
		./include/htonsv/json/json.hpp \
		./include/htonsv/server/server.h \
		./include/htonsv/server/listener.h \
		./include/htonsv/server/consumer.h \
		./include/htonsv/server/request.h \
		./include/htonsv/server/response.h \
		./include/htonsv/server/protocol.hpp \
		./include/htonsv/server/packet.hpp \
		./include/htonsv/server/text.hpp \
	-I ./source \
		./source/server/server.cpp \
		./source/server/listener.cpp \
		./source/server/consumer.cpp \
		./source/server/request.cpp \
		./source/server/response.cpp \
	external.cpp \
-pthread \
-o application.exe