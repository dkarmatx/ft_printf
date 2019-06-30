# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 20:03:07 by hgranule          #+#    #+#              #
#    Updated: 2019/06/30 21:35:07 by gdaemoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

all: $(NAME)

$(NAME):
	gcc -I libs/*/includes -I includes libs/*/srcs/*.c srcs/*.c -c
	ar rc libftprintf.a *.o

clean:
	rm -rf *.o

fclean: clean
	rm -rf *.a

re: fclean all

debug:
	gcc -I libs/*/includes -I includes libs/*/srcs/*.c srcs/*.c main.c -g