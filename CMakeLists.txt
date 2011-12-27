cmake_minimum_required(VERSION 2.8)
project(R-Type)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

include_directories(lib/SNetwork/include)

add_library(
	SNetwork
	STATIC
	./lib/SNetwork/src/ATCPClientSocket.cpp
	./lib/SNetwork/src/ATCPServerSocket.cpp
	./lib/SNetwork/src/TCPClientSocketUnix.cpp
	./lib/SNetwork/src/TCPServerSocketUnix.cpp
	./lib/SNetwork/src/UDPServerSocketUnix.cpp
	./lib/SNetwork/src/UDPClientSocketUnix.cpp
)
