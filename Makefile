# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 20:03:07 by hgranule          #+#    #+#              #
#    Updated: 2019/07/04 19:15:41 by gdaemoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
WORK_SPACE = $(shell pwd)
CC = gcc
CCFLAGS = -Wall -Werror -Wextra

O_DIR = $(WORK_SPACE)/objs
H_DIR = $(WORK_SPACE)/includes
LIBFT_DIR = $(WORK_SPACE)/libft
C_DIR = $(WORK_SPACE)/srcs
LIBH_DIR = $(LIBFT_DIR)/includes

ALL_C = ft_bf_ariphmetic.c ft_bf_cmp.c ft_bf_io.c \
		ft_bf_shifts.c ft_bigint.c ft_format_parser.c \
		ft_help_insert_b.c ft_insert_b.c ft_insert_c.c \
		ft_insert_doubles.c ft_insert_p.c ft_insert_percent.c \
		ft_insert_r.c ft_insert_s.c ft_insert_spec.c ft_printf.c \
		ft_putll_base_spec.c

ALL_O = $(patsubst %.c, %.o, $(ALL_C))

SRCS = $(patsubst %, $(C_DIR)/%, $(ALL_C))
OBJS = $(patsubst %, $(O_DIR)/%, $(ALL_O))

all: $(NAME)

libft.a:
	@make -C $(LIBFT_DIR) $@

$(NAME): o_dir $(OBJS)
	@make libft.a
	@ar rc $(NAME) $(OBJS) $(LIBFT_DIR)/libft.a;
	@ranlib $(NAME);

o_dir:
	@if ! [ -d $(O_DIR) ]; then mkdir $(O_DIR); fi;

$(O_DIR)/%.o: $(C_DIR)/%.c
	@make o_dir
	@echo "\033[1m\033[38;2;255;255;0mCompiling : \033[7m$<\033[0m\033[1m\033[38;2;255;255;0m <<\033[0m";
	@$(CC) $(CCFLAGS) -c $< -o $@ -I$(H_DIR) -I$(LIBH_DIR);

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(O_DIR)

fclean: clean
	@rm -f $(LIBFT_DIR)/libft.a
	@rm -f $(WORK_SPACE)/$(NAME)

re: fclean all
