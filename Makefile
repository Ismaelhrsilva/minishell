# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 20:08:54 by ishenriq          #+#    #+#              #
#    Updated: 2024/05/30 17:43:01 by ishenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
#CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3 -O3
CFLAGS	:=  -Ofast -g3 -O0
CC	:= cc
PRINTF	:= lib/printf/
LIBFT	:= lib/libft/
BUILD_DIR = objects/
MKDIR  := mkdir -p

HEADERS	:= -I ./include -I $(LIBFT) -I $(PRINTF) $(LIBS) -lreadline

LIBS 	:= -lm $(LIBFT)libft.a \
	-lm $(PRINTF)libftprintf.a

LDFLAGS	:= $(HEADERS) $(LIBS)

SRC_DIR := ./src/
SRCS := \
	ast/ast.c \
	ast/ast_utils.c \
	grammar/grammar.c \
	grammar/grammar_utils.c \
	parser/parser.c \
	parser/parser_utils.c \
	tokenizer/phrase.c \
	tokenizer/tokenizer.c \
	principal/read_inputs.c \
	principal/utils.c \
	principal/main.c \

SRC := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS	+=  $(SRC:%.c=$(BUILD_DIR)%.o)

define create_dir
	$(MKDIR) $(dir $@)
endef

all: libft printf $(NAME)

$(BUILD_DIR)%.o: %.c
	$(call create_dir)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

libft:
	@make -C $(LIBFT)

printf:
	@make -C $(PRINTF)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT) clean
	@make -C $(PRINTF) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean
	@make -C $(PRINTF) fclean

re: clean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC) ./include

.PHONY: all, clean, fclean, re, libft, printf, bonus
.DEFAULT_GOAL := all
