# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgranule <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 20:03:07 by hgranule          #+#    #+#              #
#    Updated: 2019/07/04 08:43:49 by hgranule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

all: $(NAME)

$(NAME):
	gcc -I libft/includes -I includes libft/srcs/*.c srcs/*.c -c
	ar rc libftprintf.a *.o

clean:
	rm -rf *.o

fclean: clean
	rm -rf *.a

re: fclean all

debug:
	gcc -I libft/includes -I includes libft/srcs/*.c srcs/*.c main.c -g