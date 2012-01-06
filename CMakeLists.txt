cmake_minimum_required(VERSION 2.8)
project(R-Type)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

include_directories(lib/SNetwork/include)

if(WIN32)

add_library(
	SNetwork
	STATIC
	./lib/SNetwork/src/ATCPClientSocket.cpp
	./lib/SNetwork/src/ATCPServerSocket.cpp
	./lib/SNetwork/src/AUDPServerSocket.cpp
	./lib/SNetwork/src/TCPClientSocketWindows.cpp
	./lib/SNetwork/src/TCPServerSocketWindows.cpp
	./lib/SNetwork/src/UDPServerSocketWindows.cpp
	./lib/SNetwork/src/UDPClientSocketWindows.cpp
)

target_link_libraries(
	SNetwork
	Ws2_32.lib
)

include_directories(include)


add_library(
	Thread
	STATIC
	./lib/Thread/src/MutexWindows.cpp
	./lib/Thread/src/ThreadWindows.cpp
	./lib/Thread/src/CondVarWindows.cpp
	./lib/Thread/src/ScopedLock.cpp
	./lib/Thread/src/ExecThread.cpp
)



include_directories(SFML-1.6/include/)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/SFML-1.6/lib/vc2008/)


add_executable(
	client
	./src/client/main.cpp
	./src/client/Client.cpp
	./src/client/ClientNetwork.cpp
	./src/client/InfoGame.cpp
	./src/protocol/PacketAggregator.cpp
	./src/client/protocol/ClientPacketManager.cpp
	./src/client/protocol/actions/ProtocolGame.cpp
	./src/client/protocol/actions/ProtocolGameDetails.cpp
	./src/client/protocol/actions/ProtocolMovement.cpp
	./src/client/protocol/actions/ProtocolLobby.cpp
	./src/protocol/PacketData.cpp
	./src/protocol/PacketFactory.cpp
	./src/client/MyMusic.cpp
	./src/client/MySound.cpp
	./src/client/GraphicClientState.cpp
	./src/client/StateStart.cpp
	./src/client/StateOptions.cpp
	./src/client/StateCreateGame.cpp
	./src/client/StateGameParameters.cpp
	./src/client/StateRoomList.cpp
	./src/client/StateRoom.cpp
	./src/client/Sfml.cpp
	./src/client/Error.cpp
	./src/client/Button.cpp
)


endif(WIN32)




if(UNIX)

SET(CMAKE_CXX_FLAGS "-Wextra -Wall -g3")

add_library(
	SNetwork
	STATIC
	./lib/SNetwork/src/ATCPClientSocket.cpp
	./lib/SNetwork/src/AUDPServerSocket.cpp
	./lib/SNetwork/src/ATCPServerSocket.cpp
	./lib/SNetwork/src/TCPClientSocketUnix.cpp
	./lib/SNetwork/src/TCPServerSocketUnix.cpp
	./lib/SNetwork/src/UDPServerSocketUnix.cpp
	./lib/SNetwork/src/UDPClientSocketUnix.cpp
)

include_directories(include)

add_library(
	Thread
	STATIC
	./lib/Thread/src/MutexUnix.cpp
	./lib/Thread/src/ThreadUnix.cpp
	./lib/Thread/src/CondVarUnix.cpp
	./lib/Thread/src/ScopedLock.cpp
	./lib/Thread/src/ExecThread.cpp
)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)

add_executable(
	client
	./src/client/main.cpp
	./src/client/Client.cpp
	./src/client/ClientNetwork.cpp
	./src/client/InfoGame.cpp
	./src/protocol/PacketAggregator.cpp
	./src/client/protocol/ClientPacketManager.cpp
	./src/client/protocol/actions/ProtocolGame.cpp
	./src/client/protocol/actions/ProtocolGameDetails.cpp
	./src/client/protocol/actions/ProtocolMovement.cpp
	./src/client/protocol/actions/ProtocolLobby.cpp
	./src/protocol/PacketData.cpp
	./src/protocol/PacketFactory.cpp
	./src/client/MyMusic.cpp
	./src/client/MySound.cpp
	./src/client/GraphicClientState.cpp
	./src/client/StateStart.cpp
	./src/client/StateOptions.cpp
	./src/client/StateCreateGame.cpp
	./src/client/StateGameParameters.cpp
	./src/client/StateRoomList.cpp
	./src/client/StateRoom.cpp
	./src/client/Sfml.cpp
	./src/client/Error.cpp
	./src/client/Button.cpp
)



endif(UNIX)

include_directories(lib/Thread/include)

include_directories(include)

SET(EXECUTABLE_NAME "server")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(
	server
	./src/server/main.cpp
	./src/protocol/PacketData.cpp
	./src/protocol/PacketFactory.cpp
	./src/server/protocol/PacketManager.cpp
	./src/server/protocol/actions/ProtocolGame.cpp
	./src/server/protocol/actions/ProtocolGameDetails.cpp
	./src/server/protocol/actions/ProtocolMovement.cpp
	./src/server/protocol/actions/ProtocolLobby.cpp
	./src/server/Server.cpp
	./src/server/GameManager.cpp
	./src/server/User.cpp
	./src/server/SafeQueue.cpp
	./src/server/ThreadData.cpp
	./src/server/ThreadPool.cpp
	./src/protocol/PacketAggregator.cpp
	./src/server/TaskManager.cpp
	./src/server/TaskNetwork.cpp
	./src/server/PacketTask.cpp
	./src/server/Game.cpp
	./src/server/Position.cpp
	./src/server/Entities.cpp
	./src/server/Monster.cpp
	./src/server/Player.cpp
	./src/server/Tile.cpp
	./src/server/AObject.cpp
	./src/server/Bullet.cpp
	#./src/server/TimerWindows.cpp
)

if(UNIX)

target_link_libraries(
	server
	SNetwork
	Thread
	pthread
)

endif(UNIX)

if(WIN32)

target_link_libraries(
	server
	SNetwork
	Thread
)

endif(WIN32)

include_directories(SFML-1.6/include)

include_directories(include)

if(WIN32)
target_link_libraries(
	client
	SNetwork
	Thread
	sfml-audio-s.lib
	sfml-graphics-s.lib
	sfml-main.lib
	sfml-network-s.lib
	sfml-system-s.lib
	sfml-window-s.lib
)

endif(WIN32)

if(UNIX)
target_link_libraries(
	client
	SNetwork
	Thread
	dl
	${SFML_LIBRARIES}
)

endif(UNIX)
