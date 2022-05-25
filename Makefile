# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 14:07:53 by cabouelw          #+#    #+#              #
#    Updated: 2022/05/25 21:05:48 by cabouelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Container
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRC =	main.cpp

INC =	containers/Vector.hpp\
		containers/Map.hpp\
		containers/Stack.hpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	@$(CC) $(OBJ) -o $(NAME)

%.o: %.cpp $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all