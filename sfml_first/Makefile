NAME_DEBUG	=	TEST
NAME_RELEASE	=	GRAPHIC

DEBUG		=	no

SRC_DIR		=	src
INCLUDE_DIR	=	include

SRCS		=	$(SRC_DIR)/main.cpp			\
			$(SRC_DIR)/DirectoryManagerUnix.cpp	\
			$(SRC_DIR)/Dll.cpp			\
			$(SRC_DIR)/DlLoader.cpp			\
			$(SRC_DIR)/ExtensionSo.cpp		\
			$(SRC_DIR)/MyMusic.cpp			\
			$(SRC_DIR)/MySound.cpp			\
			$(SRC_DIR)/GraphicClientState.cpp	\
			$(SRC_DIR)/Sfml.cpp			\
			$(SRC_DIR)/Error.cpp			\
			$(SRC_DIR)/Button.cpp



OBJS		=	$(SRCS:.cpp=.o)
LIB		=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -ldl -lpthread
CXX		=	g++
CFLAGS		=	-Wextra -Wall
ifeq ($(DEBUG), yes)
OPT		=	-ggdb
else
OPT		=	-Werror -O2
endif
RM		=	rm -f
ECHO		= 	echo

ifeq ($(DEBUG), yes)
all		: $(NAME_DEBUG)
else
all		: $(NAME_RELEASE)
endif

info_debug	:
		@$(ECHO) "[BUILD] Building : $(NAME_DEBUG) (DEBUG)"
		@$(ECHO) "[BUILD] Building options :"
		@$(ECHO) "[BUILD] Flags : $(CFLAGS)"
		@$(ECHO) "[BUILD] Debug : $(DEBUG_OPT)"
		@$(ECHO) "[BUILD] Linked Libraries : $(LIB)"

info_release	:
		@$(ECHO) "[BUILD] Building : $(NAME_RELEASE) (RELEASE)"
		@$(ECHO) "[BUILD] Building options :"
		@$(ECHO) "[BUILD] Flags : $(CFLAGS)"
		@$(ECHO) "[BUILD] Optimisation : $(OPTI_OPT)"
		@$(ECHO) "[BUILD] Linked Libraries : $(LIB)"

$(NAME_DEBUG)	: info_debug $(OBJS)
		@$(CXX) $(CFLAGS) $(OBJS) -o $(NAME_DEBUG) $(LIB)
		@$(ECHO) "[OK] Project : $(NAME_DEBUG) builded !"

$(NAME_RELEASE)	: info_release $(OBJS)
		@$(CXX) $(CFLAGS) $(OBJS) -o $(NAME_RELEASE) $(LIB)
		@$(ECHO) "[OK] Project : $(NAME_RELEASE) builded !"


clean		:
		@$(RM) $(OBJS)
		@$(RM) *~
		@$(RM) *.core
		@$(ECHO) "[OK] Cleaning directories."

fclean		: clean
		@$(RM) $(NAME_DEBUG)
		@$(RM) $(NAME_RELEASE)
		@$(ECHO) "[OK] Cleaning binary files."

re		: fclean all

.cpp.o		:
		$(CXX) -c $(CFLAGS) $(OPT) $< -o $(<:.cpp=.o) -I$(INCLUDE_DIR)
		@$(ECHO) "[OK] Building object file from : $<"
