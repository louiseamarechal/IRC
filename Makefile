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