NAME		=	client
S_NAME		=	server

# directories
SRC_DIR		=	src/
LIB_DIR		=	lib/
BIN_DIR		=	bin/
INCLUDE		=	include

MAIN_DIR	=	$(SRC_DIR)$(NAME)/
INIT_DIR	=	$(SRC_DIR)init/

SERV_DIR	=	$(SRC_DIR)$(S_NAME)/

PRTC_DIR	=	$(SRC_DIR)protocol/
USER_DIR	=	$(SRC_DIR)user/

TOOL_DIR	=	$(SRC_DIR)tools/
ERR_DIR		=	$(SRC_DIR)error/

# sources
SRCS		=	$(MAIN_DIR)main.cpp			\

S_SRCS		=	$(SERV_DIR)main.cpp			\
			$(PRTC_DIR)PacketData.cpp		\
			$(PRTC_DIR)PacketFactory.cpp		\
			$(PRTC_DIR)PacketManager.cpp		\
			$(PRTC_DIR)actions/ProtocolGame.cpp	\
			$(PRTC_DIR)actions/ProtocolGameDetails.cpp \
			$(PRTC_DIR)actions/ProtocolMovement.cpp \
			$(PRTC_DIR)actions/ProtocolLobby.cpp	\
			$(SERV_DIR)Server.cpp			\
			$(SERV_DIR)GameManager.cpp		\
			$(SERV_DIR)User.cpp			\
			$(SERV_DIR)SafeQueue.cpp		\
			$(SERV_DIR)ThreadData.cpp		\
			$(SERV_DIR)ThreadPool.cpp		\
			$(SERV_DIR)PacketAggregator.cpp		\
			$(SERV_DIR)TaskManager.cpp		\
			$(SERV_DIR)TaskNetwork.cpp		\
			$(SERV_DIR)PacketTask.cpp		\
			$(SERV_DIR)Game.cpp		\
			\

# objects
OBJS		=	$(SRCS:.cpp=.o)
S_OBJS		=	$(S_SRCS:.cpp=.o)

# libs
LIB		=	-L$(LIB_DIR) -lSNetwork -lThread

# functions
RM		=	rm -f
CXX		=	g++
CFLAGS		=	-W -Wall

# RULES
all		:	$(NAME) $(S_NAME)

lib		:

$(NAME)		:	lib $(OBJS)
			$(CXX) $(CFLAGS) $(OBJS) -o $(BIN_DIR)$(NAME) $(LIB) $(LDFLAGS)

$(S_NAME)	:	lib $(S_OBJS)
			$(CXX) $(CFLAGS) $(S_OBJS) -o $(BIN_DIR)$(S_NAME) $(LIB) $(LDFLAGS)

clean		:
			$(RM) $(OBJS) $(S_OBJS)

fclean		:	clean
			$(RM) $(BIN_DIR)$(NAME) $(BIN_DIR)$(S_NAME)

## re
re		:	fclean all

.cpp.o		:
			$(CXX) -c $(CFLAGS) $< -o $(<:.cpp=.o) -I$(INCLUDE) \
			-I$(LIB_DIR)/SNetwork/$(INCLUDE) -I$(SRC_DIR) -I$(LIB_DIR)/Thread/$(INCLUDE) -Isrc/protocol/
