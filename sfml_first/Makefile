NAME_DEBUG	=	TEST
NAME_RELEASE	=	GRAPHIC

SRC_DIR		=	src
INCLUDE_DIR	=	include

SRCS		=	$(SRC_DIR)/main.cpp			\
			$(SRC_DIR)/DirectoryManagerUnix.cpp	\
			$(SRC_DIR)/Dll.cpp			\
			$(SRC_DIR)/DlLoader.cpp			\
			$(SRC_DIR)/ExtensionSo.cpp		\
			$(SRC_DIR)/MyMusic.cpp			\
			$(SRC_DIR)/MySound.cpp			\
			$(SRC_DIR)/Sfml.cpp			\
			$(SRC_DIR)/Error.cpp


OBJS		=	$(SRCS:.cpp=.o)
LIB		=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -ldl -lpthread
CXX		=	g++
CFLAGS		=	-Wextra -Wall
DEBUG_OPT	=	-ggdb
OPTI_OPT	=	-O2
RM		=	rm -f

all		: $(NAME_DEBUG)

$(NAME_DEBUG)	: $(OBJS)
		$(CXX) $(CFLAGS) $(OBJS) -o $(NAME_DEBUG) $(LIB) $(DEBUG_OPT)

$(NAME_RELEASE)	: $(OBJS)
		$(CXX) $(CFLAGS) $(OBJS) -o $(NAME_RELEASE) $(LIB) $(OPTI_OPT)

clean		:
		$(RM) $(OBJS)
		$(RM) *~
		$(RM) *.core

fclean		: clean
		$(RM) $(NAME)

re		: fclean all

.cpp.o		:
		$(CXX) -c $(CFLAGS) $< -o $(<:.cpp=.o) -I$(INCLUDE_DIR)