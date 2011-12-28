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

include_directories(lib/Thread/include)

add_library(
	Thread
	STATIC
	./lib/Thread/src/MutexUnix.cpp
	./lib/Thread/src/ThreadUnix.cpp
	./lib/Thread/src/CondVarUnix.cpp
	./lib/Thread/src/ScopedLock.cpp
)

include_directories(include)

SET(EXECUTABLE_NAME "server")

SET(EXECUTABLE_OUTPUT_PATH ./bin)
add_executable(
	server
	./src/server/main.cpp
	./src/protocol/PacketData.cpp
	./src/protocol/PacketFactory.cpp
	./src/protocol/PacketManager.cpp
	./src/protocol/actions/ProtocolGame.cpp
	./src/protocol/actions/ProtocolGameDetails.cpp
	./src/protocol/actions/ProtocolMovement.cpp
	./src/protocol/actions/ProtocolLobby.cpp
	./src/server/Server.cpp
	./src/server/GameManager.cpp
	./src/server/User.cpp
	./src/server/SafeQueue.cpp
	./src/server/ThreadData.cpp
	./src/server/ThreadPool.cpp
	./src/server/PacketAggregator.cpp
	./src/server/TaskManager.cpp
	./src/server/TaskNetwork.cpp
	./src/server/PacketTask.cpp
	./src/server/Game.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)

target_link_libraries(
	server
	SNetwork
	Thread
)


add_executable(
	client
	./src/client/main.cpp
	./src/client/ClientNetwork.cpp
	./src/server/PacketAggregator.cpp
	./src/protocol/PacketData.cpp
	./src/protocol/PacketFactory.cpp
	./src/client/DirectoryManagerUnix.cpp
	./src/client/Dll.cpp
	./src/client/DlLoader.cpp
	./src/client/ExtensionSo.cpp
	./src/client/MyMusic.cpp
	./src/client/MySound.cpp
	./src/client/GraphicClientState.cpp
	./src/client/Sfml.cpp
	./src/client/Error.cpp
	./src/client/Button.cpp
)


include_directories(include)

target_link_libraries(
	client
	SNetwork
	Thread
	dl
	${SFML_LIBRARIES}
)

