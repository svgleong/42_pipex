# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 12:11:55 by svalente          #+#    #+#              #
#    Updated: 2023/04/19 10:51:29 by svalente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = main

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -f

all: $(NAME)

$(NAME): $(SRC:=.o)
		$(NAME) $(SRC:=.o)

clean:
	$(RM) $(SRC:=.o) $(BONUS:=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all
