/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:02:48 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/29 17:21:49 by gdaemoni         ###   ########.fr       */
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

int					ft_printf(const char *format, ...);

/*
** FORMAT PARSER FUCNTIONS
*/

char				*format_parser(char *spec, t_frmt_fs *frmt, va_list arg);

/*
** INSERTING FUNCTIONS
*/

size_t				insert_spec(t_frmt_fs *frmt, va_list arg);

/*
** INSERT STRING
*/

size_t				ft_insert_s(t_frmt_fs *frmt, va_list arg);

/*
** INSERT CHAR
*/

int					ft_insert_c(t_frmt_fs *frmt, va_list arg);

/*
** втсавляем чар н раз
*/

void				ft_putchar_n(char c, int n);

/*
** INSERT B
*/

int					ft_insert_b(t_frmt_fs *frmt, va_list arg);


/*
** HELP
*/

void				ft_putll_base_spec(long long nb, char spec);
int					ft_return_insert_b(t_frmt_fs *f, int len);
int					ft_get_len(long long *n, int base, t_frmt_fs *f);
int					ft_parse_spec(t_frmt_fs *f, int fl, long long n);
int					ft_get_base(char c);

/*
** INSERT P
*/

int					ft_insert_p(t_frmt_fs *f, va_list arg);
char				*ft_lltoa_base(long long nb, int base);

#endif
