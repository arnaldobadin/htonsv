cmake_minimum_required(VERSION "3.9")

set(PROJECT_NAME "simple-http-json-server")
set(PROJECT_VERSION "1.0.0")

project(
	"${PROJECT_NAME}"
	VERSION "${PROJECT_VERSION}"
	DESCRIPTION "Just a simple HTTP JSON Server."
)

set(LIBRARY_NAME "server")

add_library("${LIBRARY_NAME}" STATIC
	lib/json.hpp
	src/server.h
	src/server.cpp
	src/listener.h
	src/listener.cpp
	src/consumer.h
	src/consumer.cpp
	src/request.h
	src/request.cpp
	src/response.h
	src/response.cpp
	src/packet.hpp
	src/protocol.hpp
	src/text.hpp
)

set_target_properties("${LIBRARY_NAME}" PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION 1
	PUBLIC_HEADER api/server.h
)

include(GNUInstallDirs)

configure_file(cmake/server.pc.in server.pc @ONLY)

target_include_directories("${LIBRARY_NAME}" PRIVATE lib)
target_include_directories("${LIBRARY_NAME}" PRIVATE src)

target_link_libraries("${LIBRARY_NAME}" pthread)

#set_target_properties("${LIBRARY_NAME}" PROPERTIES PREFIX "")
#set_target_properties("${LIBRARY_NAME}" PROPERTIES OUTPUT_NAME "${LIBRARY_NAME}")
#set_target_properties("${LIBRARY_NAME}" PROPERTIES SUFFIX ".lib")

install(TARGETS "${LIBRARY_NAME}"
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/api
)

install(
	FILES ${CMAKE_BINARY_DIR}/server.pc
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)