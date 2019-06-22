/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 21:22:03 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/22 08:03:22 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

void		ft_putchar_n(char c, int n, size_t len)
{
	if (n > 0 && n > len)
	{
		while (n)
		{
			write(1, &c, 1);
			n--;
		}
	}
}

size_t		ft_insert_s(t_frmt_fs *f, va_list arg)
{
	char	*str;
	size_t	len;
	size_t	size;

	str = va_arg(arg, char*);
	size = f->field_len;
	if (f->ispre == 1 && !f->precision)
	{
		ft_putchar_n(f->zerofill ? '0' : ' ', size, 0);
		return (size);
	}
	len = ft_strlen(str);
	if (!f->orient)
	{
		ft_putchar_n(f->zerofill ? '0' : ' ',
		!f->ispre ? size - len : size - f->precision, len);
		write(1, str, f->ispre == 1 ? f->precision : len);
	}
	else
	{
		write(1, str, f->ispre == 1 ? f->precision : len);
		ft_putchar_n(f->zerofill ? '0' : ' ',
		!f->ispre ? size - len : size - f->precision, len);
	}
	return (size && size > f->precision ? size > len ? size : len : f->ispre ? f->precision : len);
}
