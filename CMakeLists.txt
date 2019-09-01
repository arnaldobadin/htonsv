cmake_minimum_required(VERSION "3.9")

set(PROJECT_NAME "project-scope")
set(PROJECT_VERSION "1.0.0")

set(LIBRARY_NAME "htonsv")
set(LIBRARY_VERSION "1.0.0")

project(
	"${PROJECT_NAME}"
	VERSION "${PROJECT_VERSION}"
	DESCRIPTION "Just an easier way to communicate."
)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_library("${LIBRARY_NAME}" STATIC
	source/server/server.cpp
	source/server/listener.cpp
	source/server/consumer.cpp
	source/server/request.cpp
	source/server/response.cpp
)

set_target_properties("${LIBRARY_NAME}" PROPERTIES
	VERSION "${LIBRARY_VERSION}"
	SOVERSION 1
)

include(GNUInstallDirs)

target_include_directories("${LIBRARY_NAME}"
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/source
)

find_package(Threads REQUIRED)
target_link_libraries("${LIBRARY_NAME}" PUBLIC Threads::Threads)

configure_file(cmake/${LIBRARY_NAME}.pc.in ${LIBRARY_NAME}.pc @ONLY)

install(TARGETS "${LIBRARY_NAME}"
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
	FILES ${CMAKE_BINARY_DIR}/${LIBRARY_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILES_MATCHING PATTERN "*.h*"
)