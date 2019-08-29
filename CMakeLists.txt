cmake_minimum_required(VERSION "3.9")

set(PROJECT_NAME "simple-http-json-server")
set(PROJECT_VERSION "1.0.0")
set(LIBRARY_NAME "htonsv")
set(EXECUTABLE_NAME "something")

project(
	"${PROJECT_NAME}"
	VERSION "${PROJECT_VERSION}"
	DESCRIPTION "An easier way to communicate."
)

add_library("${LIBRARY_NAME}" STATIC
	include/htonsv.hpp
	source/json/json.hpp
	source/server/server.h
	source/server/server.cpp
	source/server/listener.h
	source/server/listener.cpp
	source/server/consumer.h
	source/server/consumer.cpp
	source/server/request.h
	source/server/request.cpp
	source/server/response.h
	source/server/response.cpp
	source/server/packet.hpp
	source/server/protocol.hpp
	source/server/text.hpp
)

target_include_directories("${LIBRARY_NAME}"
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source/
)

include(GNUInstallDirs)

find_package(Threads)
target_link_libraries("${LIBRARY_NAME}" "${CMAKE_THREAD_LIBS_INIT}")

configure_file(cmake/server.pc.in server.pc @ONLY)

add_executable("${EXECUTABLE_NAME}" external.cpp)

target_link_libraries("${EXECUTABLE_NAME}" "${LIBRARY_NAME}")

install(TARGETS "${EXECUTABLE_NAME}" DESTINATION bin)