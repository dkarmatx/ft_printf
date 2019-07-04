/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:14:44 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/07/04 10:54:12 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int				ft_insert_p(t_frmt_fs *f, va_list arg)
{
	int		len[2];
	char	*str;

	ft_bzero(len, 8);
	f->precision = (!f->ispre || f->precision) ? f->precision : 0;
	str = ft_lltoa_base((long long)(va_arg(arg, int*)), 16);
	(!f->ispre || f->precision) ? len[1] = (ft_strlen(str)) : 0;
	if (!f->orient)
	{
		len[0] += ft_putchar_n(' ', f->ispre && f->precision > len[1] ?\
		f->field_len - f->precision - 2 : f->field_len - 2 - len[1]);
		len[0] += write(1, "0x", 2);
		len[0] += ft_putchar_n('0', f->precision - len[1]);
		(!f->ispre || f->precision) ? (len[0] += write(1, str, len[1])) : 0;
	}
	else
	{
		len[0] += write(1, "0x", 2);
		len[0] += ft_putchar_n('0', f->precision - len[1]);
		(!f->ispre || f->precision) ? (len[0] += write(1, str, len[1])) : 0;
		len[0] += ft_putchar_n(' ', f->ispre && f->precision > len[1] ?\
		f->field_len - f->precision - 2 : f->field_len - 2 - len[1]);
	}
	free(str);
	return (len[0]);
}
