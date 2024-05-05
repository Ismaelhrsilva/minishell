# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 20:55:32 by ishenriq          #+#    #+#              #
#    Updated: 2024/01/04 19:28:06 by ishenriq         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #


#Name
NAME = libftprintf.a

#Compiler and flags
CC = cc
CFLAGS =  -Wall -Wextra -Werror -g3 -O0

#arquivos e objetos
PT_C = ft_printf.c \
utils_1.c \
utils_2.c

INCLUDES = ft_printf.h

OBJS = $(PT_C:.c=.o)

#Rules
all: $(NAME)

$(NAME): $(OBJS)
	ar rc -s $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

