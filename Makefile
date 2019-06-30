# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 20:03:07 by hgranule          #+#    #+#              #
#    Updated: 2019/06/30 20:55:05 by gdaemoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

debug:
	gcc -I libs/*/includes -I includes libs/*/srcs/*.c srcs/*.c main.c -g

all: $(NAME)

$(NAME):
	gcc -I libs/*/includes -I includes libs/*/srcs/*.c srcs/*.c -c
	ar rc libftprintf.a *.o
	rm -rf *.o

clean:
	rm -rf *.o

fclean: clean
	rm -rf *.a

re: fclean all