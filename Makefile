# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 20:03:07 by hgranule          #+#    #+#              #
#    Updated: 2019/06/23 10:57:20 by gdaemoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc -I libs/*/includes -I includes libs/*/srcs/*.c srcs/*.c main.c -g

ma:
	gcc -I libs/*/includes -I includes libs/*/srcs/*.c srcs/*.c -c
	ar rc libftprintf.a *.o
	rm -rf *.o