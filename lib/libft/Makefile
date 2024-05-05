# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 20:55:32 by ishenriq          #+#    #+#              #
#    Updated: 2024/03/03 18:45:54 by ishenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Name
NAME = libft.a

#Compiler and flags
CC = cc
CFLAGS =  -Wall -Wextra -Werror -g3 -O0

#arquivos e objetos
PT_C = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strncmp.c \
ft_strmapi.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
gnl/get_next_line.c \
gnl/get_next_line_utils.c \
ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstdelone_bonus.c \
ft_lstclear_bonus.c \
ft_lstiter_bonus.c \
ft_lstlast_bonus.c \
ft_lstmap_bonus.c \
ft_lstnew_bonus.c \
ft_lstsize_bonus.c \
ft_split_quote.c \
ft_strrplc.c

INCLUDES = ./ ./gnl

OBJS = $(PT_C:.c=.o)

#Rules
all: $(NAME)

$(NAME): $(OBJS)
	ar rc -s $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

