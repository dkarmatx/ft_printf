# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 20:03:07 by hgranule          #+#    #+#              #
#    Updated: 2019/07/04 20:52:03 by gdaemoni         ###   ########.fr        #
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

ART = ft_toupper.o ft_tolower.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isalnum.o ft_isprint.o ft_isspace.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o ft_putll_base_fd.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_hexdump.o ft_strlen.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_memdel.o ft_memcpy.o ft_dlstnew.o ft_dlstpush.o ft_dlstunshift.o ft_dlstget.o ft_dlstrget.o ft_dlstinsert.o ft_dlstrmelem.o ft_dlstcut.o ft_dlstdel.o ft_dlstshift.o ft_dlstswap.o ft_dlst_gnsort.o ft_dlst_rgnsort.o ft_memdup.o ft_memcpy.o ft_memdel.o ft_memalloc.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o ft_memcmp.o ft_realloc.o ft_memdup.o ft_strnew.o ft_strdup.o ft_strchr.o ft_strrchr.o ft_strstr.o ft_strnstr.o ft_strcpy.o ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strlen.o ft_strnlen.o ft_strcmp.o ft_strncmp.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_lltoa_base.o ft_itoa.o ft_atoll_base.o ft_atoi_base.o ft_atoi.o ft_countw_delim.o ft_strccpy.o ft_isspace.o ft_memchr.o ft_bzero.o ft_memcpy.o ft_memdel.o ft_memalloc.o
ARTF = $(patsubst %, $(LIBFT_DIR)/objs/%, $(ART))


all: $(NAME)

libft.a:
	@make -C $(LIBFT_DIR)

$(NAME): libft.a o_dir $(OBJS)
	@ar rc $(NAME) $(ARTF) $(OBJS);
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
	@rm -rf $(WORK_SPACE)/tmp.a

fclean: clean
	@rm -f $(LIBFT_DIR)/libft.a
	@rm -f $(WORK_SPACE)/$(NAME)

re: fclean all
