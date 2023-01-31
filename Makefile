# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 14:24:03 by jbouyer           #+#    #+#              #
#    Updated: 2023/01/31 12:29:43 by lmarecha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

FLAGS = -Wall -Wextra -Werror -std=c++98 -g
SRC =	commands.cpp \
		Server.cpp \
		User.cpp \
		Utils.cpp \
		Reply.cpp \
		main.cpp

HEADER = commands.hpp Server.hpp User.hpp Utils.hpp Reply.hpp
OBJ	=	${SRC:.cpp=.o}

all: $(NAME)

$(NAME):$(OBJ)
		c++ -o $(NAME) $(OBJ) $(FLAGS)

%.o : %.cpp $(HEADER)
		c++ $(FLAGS) -c $< -o $@

clean :
		rm -rf $(OBJ)

fclean :
		rm -rf $(NAME) $(OBJ)

re : fclean
	make all

.PHONY: all clean fclean re 