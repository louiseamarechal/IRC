# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 14:24:03 by jbouyer           #+#    #+#              #
#    Updated: 2023/01/27 14:25:27 by jbouyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

FLAGS = -Wall -Wextra -Werror -std=c++98 -g
SRC = main.cpp commands.cpp Server.cpp User.cpp Utils.cpp 
HEADER = commands.hpp Server.hpp User.hpp Utils.hpp
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