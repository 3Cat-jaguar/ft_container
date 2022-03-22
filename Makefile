# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 09:38:00 by ylee              #+#    #+#              #
#    Updated: 2022/02/20 17:46:54 by ylee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CFLAG = -Wall -Wextra -Werror -std=c++98
RM = rm -rf
NAME = ft_container
SRC = main.cpp\
	test_vector.cpp\
	test_stack.cpp\
	test_map.cpp

OBJ = $(SRC:.cpp=.o)

NAMESPACE = -DTYPE_NAMESPACE=std
#NAMESPACE = -DTYPE_NAMESPACE=ft

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

$(OBJ):$(SRC)
	$(CC) $(CFLAG) -c $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:all clean fclean re


