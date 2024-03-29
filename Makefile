# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:47:43 by jbouyer           #+#    #+#              #
#    Updated: 2023/03/02 13:47:48 by jbouyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
				commands/JOIN.cpp \
				commands/PART.cpp \
				commands/PING.cpp \
				commands/OPER.cpp \
				commands/QUIT.cpp \
				commands/NAMES.cpp \
				commands/PRIVMSG.cpp \
				commands/KICK.cpp \
				commands/KILL.cpp \
				commands/NOTICE.cpp
		
CLASSFILE	=	server/Server.cpp \
				user/User.cpp \
				channel/Channel.cpp

SRC			=	$(addprefix $(SRCDIR), $(SRCFILE)) $(addprefix $(SRCDIR), $(CLASSFILE))


#------------------------------------#
#              INCLUDES              #
#------------------------------------#

INCLDIR			=	includes/

INCLSRCFILES 	=	commands.hpp \
					reply.hpp \
					utils.hpp 

INCLCLASSFILES	=	server/Server.hpp \
					user/User.hpp \
					channel/Channel.hpp

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