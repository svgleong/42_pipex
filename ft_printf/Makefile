# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 10:48:12 by svalente          #+#    #+#              #
#    Updated: 2022/11/24 15:25:39 by svalente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_functions ft_verify ft_printf

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs

all: $(NAME)

$(NAME): $(SRC:=.o)
			$(AR) $(NAME) $(SRC:=.o)

clean:
	$(RM) $(SRC:=.o) $(BONUS:=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all