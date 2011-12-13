NAME		=	r-type
S_NAME		=	$(NAME)_server

# directories
SRC_DIR		=	src/
LIB_DIR		=	lib/
BIN_DIR		=	bin/
INCLUDE		=	include/

MAIN_DIR	=	$(SRC_DIR)$(NAME)/
INIT_DIR	=	$(SRC_DIR)init/

SERV_DIR	=	$(SRC_DIR)$(S_NAME)/

PRTC_DIR	=	$(SRC_DIR)protocol/

TOOL_DIR	=	$(SRC_DIR)tools/
ERR_DIR		=	$(SRC_DIR)error/

# sources
SRCS		=	$(MAIN_DIR)main.cpp			\
			$(MAIN_DIR)$(NAME).cpp			\
			\

S_SRCS		=	$(SERV_DIR)main.cpp			\
			$(SERV_DIR)Server.cpp			\
			$(SERV_DIR)User.cpp

# objects
OBJS		=	$(SRCS:.cpp=.o)
S_OBJS		=	$(S_SRCS:.cpp=.o)

# libs
LIB		=	-L$(LIB_DIR) -lSNetwork

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
			$(CXX) -c $(CFLAGS) $< -o $(<:.cpp=.o) -I$(INCLUDE) -I$(LIB_DIR)/SNetwork/$(INCLUDE)
