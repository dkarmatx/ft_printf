/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 21:22:03 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/30 21:32:46 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int inline		ft_putchar_n(char c, ssize_t n)
{
	int		len;

	len = -1;
	while (++len < n)
	{
		write(1, &c, 1);
	}
	return (len);
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
		str = "(null)";
	len = ft_strlen(str);
	return (ft_print_str(f, len, size, str));
}
