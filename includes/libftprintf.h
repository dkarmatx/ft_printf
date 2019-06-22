/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:02:48 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/22 07:44:43 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "libft.h"

/*
** bufflen - Размер буфера вывода для int. для float количество символов слева
** prelen - точность
** base - система счисления
** orient - если 0 то выравнивание по правому краю иначе по левому
** zerofill - заполнение 0 или нет
** asteriks - если 0b00 x.x, если 0b10 *.x, если 0b01 x.*, 0b11 *.*
** sharp - # ? 1 : 0
** sign - требуется вывод знака или нет
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
	char			asteriks;
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

/*
** INSERT STRING
*/

size_t		ft_insert_s(t_frmt_fs *frmt, va_list arg);

/*
** INSERT CHAR
*/

int			ft_insert_c(t_frmt_fs *frmt, va_list arg);

/*
** втсавляем чар н раз если н > лен
*/

void		ft_putchar_n(char c, int n, size_t len);


#endif