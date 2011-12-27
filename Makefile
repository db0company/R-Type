# name
NAME_DEBUG	=	client_debug
NAME_RELEASE	=	client_release
S_NAME		=	server

# debug
DEBUG		=	yes

# directories
SRC_DIR		=	src/
LIB_DIR		=	lib/
BIN_DIR		=	bin/
INCLUDE		=	include

MAIN_DIR	=	$(SRC_DIR)$(NAME)/
INIT_DIR	=	$(SRC_DIR)init/

SERV_DIR	=	$(SRC_DIR)$(S_NAME)/
CLIE_DIR	=	$(SRC_DIR)client/

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
			$(SERV_DIR)PacketAggregator.cpp

C_SRCS		=	$(CLIE_DIR)/main.cpp			\
			$(CLIE_DIR)/DirectoryManagerUnix.cpp	\
			$(CLIE_DIR)/Dll.cpp			\
			$(CLIE_DIR)/DlLoader.cpp		\
			$(CLIE_DIR)/ExtensionSo.cpp		\
			$(CLIE_DIR)/MyMusic.cpp			\
			$(CLIE_DIR)/MySound.cpp			\
			$(CLIE_DIR)/GraphicClientState.cpp	\
			$(CLIE_DIR)/Sfml.cpp			\
			$(CLIE_DIR)/Error.cpp			\
			$(CLIE_DIR)/Button.cpp

# objects
OBJS		=	$(SRCS:.cpp=.o)
S_OBJS		=	$(S_SRCS:.cpp=.o)
C_OBJS		=	$(C_SRCS:.cpp=.o)

# libs
LIB		=	-L$(LIB_DIR) -lSNetwork -lThread
C_LIB		=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -ldl -lpthread

# functions
RM		=	rm -f
CXX		=	g++
CFLAGS		=	-Wextra -Wall

ifeq ($(DEBUG), yes)
OPT		=	-ggdb
else
OPT		=	-Werror -O2
endif

ECHO		= 	echo

# RULES
ifeq ($(DEBUG), yes)
all		: 	$(NAME_DEBUG) $(S_NAME)
else
all		: 	$(NAME_RELEASE) $(S_NAME)
endif

lib		:

##$(NAME)		:	lib $(OBJS)
##			$(CXX) $(CFLAGS) $(OBJS) -o $(BIN_DIR)$(NAME) $(LIB) $(LDFLAGS)
info_debug	:
			@$(ECHO) "[BUILD] Building : $(NAME_DEBUG) (DEBUG)"
			@$(ECHO) "[BUILD] Building options :"
			@$(ECHO) "[BUILD] Flags : $(CFLAGS)"
			@$(ECHO) "[BUILD] Debug : $(DEBUG_OPT)"
			@$(ECHO) "[BUILD] Linked Libraries : $(C_LIB)"

info_release	:
			@$(ECHO) "[BUILD] Building : $(NAME_RELEASE) (RELEASE)"
			@$(ECHO) "[BUILD] Building options :"
			@$(ECHO) "[BUILD] Flags : $(CFLAGS)"
			@$(ECHO) "[BUILD] Optimisation : $(OPTI_OPT)"
			@$(ECHO) "[BUILD] Linked Libraries : $(C_LIB)"

$(NAME_DEBUG)	: 	info_debug $(C_OBJS)
			@$(CXX) $(CFLAGS) $(C_OBJS) -o $(NAME_DEBUG) $(C_LIB)
			@$(ECHO) "[OK] Project : $(NAME_DEBUG) builded !"

$(NAME_RELEASE)	:	 info_release $(C_OBJS)
			@$(CXX) $(CFLAGS) $(C_OBJS) -o $(NAME_RELEASE) $(C_LIB)
			@$(ECHO) "[OK] Project : $(NAME_RELEASE) builded !"

$(S_NAME)	:	lib $(S_OBJS)
			$(CXX) $(CFLAGS) $(S_OBJS) -o $(BIN_DIR)$(S_NAME) $(LIB) $(LDFLAGS)

clean		:
			@$(RM) $(C_OBJS) $(S_OBJS)
			@$(ECHO) "[OK] Cleaning directories."

fclean		:	clean
			@$(RM) $(BIN_DIR)$(NAME_RELEASE) $(BIN_DIR)$(NAME_DEBUG) $(BIN_DIR)$(S_NAME)

## re
re		:	fclean all

.cpp.o		:
			$(CXX) -c $(CFLAGS) $(OPT) $< -o $(<:.cpp=.o) -I$(INCLUDE) \
			-I$(LIB_DIR)/SNetwork/$(INCLUDE) -I$(SRC_DIR) -I$(LIB_DIR)/Thread/$(INCLUDE) -Isrc/protocol/
			@$(ECHO) "[OK] Building object file from : $<"
