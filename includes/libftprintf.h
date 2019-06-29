/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:02:48 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/29 20:39:12 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "libft.h"

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
typedef struct		s_flags_specifier
{
	int				error;
	int				type;
	int				size;
	int				field_len;
	int				precision;
	char			orient;
	char			zerofill;
	char			sharp;
	char			sign;
	char			ispre;
	char			spec;
}					t_frmt_fs;

int			ft_printf(const char *format, ...);

/*
** FORMAT PARSER FUCNTIONS
*/

char		*format_parser(char *spec, t_frmt_fs *frmt, va_list arg);

/*
** INSERTING FUNCTIONS
*/

size_t		insert_spec(t_frmt_fs *frmt, va_list arg);
int			put_float(t_frmt_fs *f, const char *fl, const char *fint, size_t len);
int			put_n_char(char c, ssize_t n);

#endif