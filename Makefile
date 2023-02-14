#------------------------------------#
#             COMPILATION            #
#------------------------------------#

NAME	=	ircserv

FLAGS	=	-Wall -Wextra -Werror -std=c++98 -g


#------------------------------------#
#                SOURCES             #
#------------------------------------#

SRCDIR		=	srcs/

SRCFILE		=	main.cpp \
				utils.cpp \
				reply.cpp \
				commands/NICK.cpp \
				commands/USER.cpp \
				commands/MOTD.cpp \
				commands/PING.cpp \
				commands/OPER.cpp 
		
CLASSFILE	=	server/Server.cpp \
				user/User.cpp

SRC			=	$(addprefix $(SRCDIR), $(SRCFILE)) $(addprefix $(SRCDIR), $(CLASSFILE))


#------------------------------------#
#              INCLUDES              #
#------------------------------------#

INCLDIR			=	includes/

INCLSRCFILES 	=	commands.hpp \
					reply.hpp \
					utils.hpp 

INCLCLASSFILES	=	server/Server.hpp \
					user/User.hpp

INCLUDES		=	$(addprefix $(INCLDIR), $(INCLSRCFILES)) $(addprefix $(SRCDIR), $(INCLCLASSFILES))


#------------------------------------#
#               OBJECTS              #
#------------------------------------#

OBJDIR	=	objs/
OBJ		=	$(subst $(SRCDIR),$(OBJDIR),$(SRC:.cpp=.o))


#------------------------------------#
#               RULES                #
#------------------------------------#

all: $(NAME)

$(NAME):$(OBJ)
		c++ -o $(NAME) $(OBJ) $(FLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(INCLUDES) 
		@mkdir -p `dirname $@`
		c++ $(FLAGS) -c $< -o $@ -I $(INCLDIR) -I $(SRCDIR)

clean :
		rm -rf $(OBJDIR)

fclean :
		rm -rf $(NAME) $(OBJDIR)

re : fclean
	make all

.PHONY: all clean fclean re 