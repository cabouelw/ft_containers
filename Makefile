# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 14:07:53 by cabouelw          #+#    #+#              #
#    Updated: 2022/02/15 14:09:27 by cabouelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Containers
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRC =	main.cpp\
		containers/Vector.cpp\

INC =	ft_containers.hpp\
		containers/Vector.hpp\

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