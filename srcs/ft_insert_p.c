/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:14:44 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/28 15:49:22 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

static int		ft_return_insert_p(t_frmt_fs *f, int len)
{
	if (f->precision >= f->field_len && f->precision >= len)
		return (f->precision + 2);
	else if (f->field_len > f->precision && f->field_len > len)
		return (f->field_len);
	else
		return (len + 2);
	return (0);
}

int				ft_insert_p(t_frmt_fs *f, va_list arg)
{
	int		*n;
	int		len;
	char	*str;

	n = va_arg(arg, int*);
	str = ft_lltoa_base((long long)n, 16);
	len = (ft_strlen(str));
	if (!f->orient)
	{
		ft_putchar_n(' ', f->ispre && f->precision > len ?\
		f->field_len - f->precision - 2 : f->field_len - 2 - len);
		write(1, "0x", 2);
		ft_putchar_n('0', f->precision - len);
		write(1, str, len);
	}
	else
	{
		write(1, "0x", 2);
		ft_putchar_n('0', f->precision - len);
		write(1, str, len);
		ft_putchar_n(' ', f->ispre && f->precision > len ?\
		f->field_len - f->precision - 2 : f->field_len - 2 - len);
	}
	return (ft_return_insert_p(f, len));
}
