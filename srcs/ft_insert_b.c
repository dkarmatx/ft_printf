/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:10:50 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/29 21:29:21 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int					ft_parse_spec(t_frmt_fs *f, int fl, long long n)
{
	if (fl == 1 && (f->spec == 'o' || f->spec == 'O') && f->sharp && n != 0)
		write(1, "0", 1);
	else if (fl == 1 && f->sharp
	&& n != 0 && f->spec == 'x')
		write(1, "0x", 2);
	else if (fl == 1 && f->sharp
	&& n != 0 && f->spec == 'X')
		write(1, "0X", 2);
	else if ((f->spec == 'o' || f->spec == '0') && n != 0)
		return (1);
	else if ((f->spec == 'X' || f->spec == 'x') && n != 0)
		return (2);
	return (0);
}

long long			ft_get_num(t_frmt_fs *f, va_list arg)
{
	if (f->size == 1 && ft_memchr("uoxX", (int)f->spec, 4))
		return ((unsigned char)va_arg(arg, int));
	if (f->size == 1)
		return ((char)va_arg(arg, int));
	else if (f->size == 2 && ft_memchr("uoxX", (int)f->spec, 4))
		return (va_arg(arg, unsigned int));
	else if (f->size == 2)
		return ((short)va_arg(arg, int));
	else if (f->size == 4 && ft_memchr("uoxX", (int)f->spec, 4))
		return ((unsigned)va_arg(arg, int));
	else if (f->size == 4 && ft_memchr("di", (int)f->spec, 2))
		return (va_arg(arg, int));
	else if (f->size == 8 || ft_memchr("uUoOxX", (int)f->spec, 6))
		return (va_arg(arg, unsigned long long));
	else if (f->size == 8 || f->spec == 'D')
		return (va_arg(arg, long long));
	return (0);
}

static void			ft_print_b_else(t_frmt_fs *f, long long n, char *s, int l)
{
	if ((!ft_strcmp(s, "-") && !ft_memchr("uUoOxX", (int)f->spec, 6))
	|| f->sign == 1)
		write(1, s, 1);
	ft_parse_spec(f, 1, n);
	ft_putchar_n('0', f->precision - l + ft_parse_spec(f, 0, n));
	ft_putll_base_spec(n, f->spec);
	ft_putchar_n(' ', f->field_len -\
	(f->precision > l ? f->precision : l + ft_parse_spec(f, 0, n)));
}

static void			ft_print_d(t_frmt_fs *f, long long n, char *sign, int len)
{
	int	fl;

	if ((fl = 0) == 0 && !f->orient)
	{
		if (f->field_len > f->precision && f->field_len > len)
		{
			if (((((f->precision > f->field_len || !f->ispre)
			&& !(f->field_len > len && !f->zerofill)
			&& (!ft_strcmp(sign, "-") || f->sign == 1) && (fl = 1) == 1)
			&& !ft_memchr("uUoOxX", (int)f->spec, 6))
			|| (f->precision > f->field_len && f->sign == 1 && (fl = 1) == 1)))
				write(1, sign, 1);
			ft_putchar_n(f->zerofill && !f->ispre ? '0' : ' ',
			f->field_len -\
			(f->precision > len ? f->precision : len));
		}
		if (fl == 0 && !ft_memchr("uUoOxX", (int)f->spec, 6)
		&& (!ft_strcmp(sign, "-") || f->sign == 1))
			write(1, sign, 1);
		ft_parse_spec(f, 1, n);
		ft_putchar_n('0', f->precision - len);
		ft_putll_base_spec(n, f->spec);
		return ;
	}
	ft_print_b_else(f, n, sign, len);
}

int					ft_insert_b(t_frmt_fs *f, va_list arg)
{
	long long	n;
	char		*sign;
	int			len;
	int			fl;

	n = ft_get_num(f, arg);
	sign = n >= 0 ? "+" : "-";
	len = ft_get_len(&n, ft_get_base(f->spec), f);
	len += (int)(f->sign && !ft_strcmp(sign, "+"));
	f->precision += f->precision && (f->sign || !ft_strcmp(sign, "-")) ? 1 : 0;
	if (f->ispre && !f->precision && !n && !f->sign)
		return (ft_return_insert_b(f, len - 1));
	if (n == 0 && f->ispre && !f->precision && f->sign)
	{
		write(1, f->sign == 1 ? "+" : " ", 1);
		return (1);
	}
	if (f->sign == 2 && !ft_strcmp(sign, "+"))
		write(1, f->sign == 1 ? "+" : " ", 1);
	ft_print_d(f, n, sign, len);
	return (ft_return_insert_b(f, len));
}
