/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:02:48 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/30 15:21:43 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "libft.h"
# include "longnumber.h"

/*
** error - зарезервиравано под ошибки
** type - типы спецификаторов от 1 до 5
** size - размер в байтах
** field_len - длина поля (числа по пизде)
** precision - точность
** orient - если 0 то правое, если 1 то левое выравнивания
** zerofill - заполнение нулями
** sharp - ШАРП
** sign - знак
** ispre - есть ли пресижн
** spec - спецификатор
*/
typedef struct	s_flags_specifier
{
	int			error;
	int			type;
	int			size;
	int			field_len;
	int			precision;
	char		orient;
	char		zerofill;
	char		sharp;
	char		sign;
	char		ispre;
	char		spec;
}				t_frmt_fs;

int				ft_printf(const char *format, ...);

/*
** FORMAT PARSER FUCNTIONS
*/

char			*format_parser(char *spec, t_frmt_fs *frmt, va_list arg);

/*
** INSERTING FUNCTIONS
*/

size_t			insert_spec(t_frmt_fs *frmt, va_list arg);
int				ft_putchar_n(char c, ssize_t n);

/*
** FLOAT INSERTING
*/

int				put_fl(t_frmt_fs *f, const char *fl, const char *i, size_t l);
size_t			insert_doubles(t_frmt_fs *frtmt, va_list arg);

#endif
