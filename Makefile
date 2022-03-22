# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 09:38:00 by ylee              #+#    #+#              #
#    Updated: 2022/03/23 06:05:10 by ylee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CFLAG = -Wall -Wextra -Werror -std=c++98
TYPE = -DTYPE=1 # STL test
#TYPE = -DTYPE=2 # my container test
RM = rm -rf
NAME = ft_container
SRC = main.cpp\
	test_map.cpp\
	test_stack.cpp\
	test_vector.cpp\

OBJ = $(SRC:.cpp=.o)


all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(TYPE) $(OBJ) -o $(NAME)

$(OBJ):$(SRC)
	$(CC) $(CFLAG) $(TYPE) -c $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:all clean fclean re


