# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 09:38:00 by ylee              #+#    #+#              #
#    Updated: 2022/03/23 16:26:37 by ylee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++
CFLAG = -Wall -Wextra -Werror -std=c++98
STLTYPE = -DTYPE=1 # STL test
MCTYPE = -DTYPE=2 # my container test
RM = rm -rf
STLNAME = STL_containers
MCNAME = ft_containers
STLOUT = ./STL
MCOUT = ./mycontainer
DIFF = ./diff
SRC = main.cpp\
	test_map.cpp\
	test_stack.cpp\
	test_vector.cpp\

all: run

run : $(SRC) # STL 과 ft_containers 실행 후 비교파일 만드는 작업 자동화
	$(CC) $(CFLAG) $(MCTYPE) $(SRC) -o $(MCNAME)
	./$(MCNAME) > $(MCOUT)
	$(CC) $(CFLAG) $(STLTYPE) $(SRC) -o $(STLNAME)
	./$(STLNAME) > $(STLOUT)
	diff $(STLOUT) $(MCOUT) > $(DIFF); [ $$? -eq 1 ]

clean:
	$(RM) $(MCOUT) $(STLOUT) $(DIFF)

fclean: clean
	$(RM) $(MCNAME) $(STLNAME)

re: fclean all

.PHONY:all clean fclean re run


