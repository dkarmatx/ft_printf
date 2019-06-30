/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 21:22:03 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/30 20:25:29 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

void			ft_putchar_n(char c, int n)
{
	if (n > 0)
	{
		while (n)
		{
			write(1, &c, 1);
			n--;
		}
	}
}

size_t			ft_print_str(t_frmt_fs *f, size_t len, size_t size, char *str)
{
	if (!f->orient)
	{
		ft_putchar_n(f->zerofill ? '0' : ' ',
		(unsigned)f->precision > len || !f->ispre \
		? size - len : size - f->precision);
		write(1, str, f->ispre && (unsigned)f->precision \
		< len ? f->precision : len);
	}
	else
	{
		write(1, str, f->ispre && (unsigned)f->precision \
		< len ? f->precision : len);
		ft_putchar_n(f->zerofill ? '0' : ' ',
		(unsigned)f->precision > len || !f->ispre \
		? size - len : size - f->precision);
	}
	if (size >= len)
		return (size);
	else if (!f->ispre || len < (unsigned)f->precision)
		return (len);
	else
		return (f->precision);
}

size_t			ft_insert_s(t_frmt_fs *f, va_list arg)
{
	char	*str;
	size_t	len;
	size_t	size;

	str = va_arg(arg, char*);
	size = f->field_len;
	if (f->ispre && !f->precision)
	{
		ft_putchar_n(f->zerofill ? '0' : ' ', size);
		return (size);
	}
	if (!str)
		str = ft_strsub("(null)", 0, 6);
	len = ft_strlen(str);
	return (ft_print_str(f, len, size, str));
}
