/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:10:50 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/23 20:11:45 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int			ft_get_raz(long long n, int base)
{
	int rez;

	rez = 0;
	if (n <= 0)
	{
		n *= -1;
		rez++;
	}
	while(n > 0)
	{
		n = n / base;
		++rez;
	}
	return (rez);
}

int			ft_insert_b(t_frmt_fs *f, va_list arg)
{
	long long	n;
	int			len;
	int			fl;

	fl = 0;
	if (f->size == 1)
		n = (char)va_arg(arg, int);	
	else if (f->size == 2)
		n = (short)va_arg(arg, int);
	else if (f->size == 4)
		n = va_arg(arg, int);
	else if (f->size == 8)
		n = va_arg(arg, long long);
	len = ft_get_raz(n, 10);
	if (f->ispre && !f->precision && !n)
		return (0);
	if (n < 0 && ((n = n * -1) && ++f->sign) && ++fl)
	{
		if (!f->field_len || f->zerofill || f->ispre)
			write(1, "-", 1);
	}
	else if (f->sign == 1 && n >= 0 && ++len)
		write(1, "+", 1);
	else if (f->sign == 2 && n >= 0 && ++len)
		write(1, " ", 1);
	
	if (f->ispre)
		ft_putchar_n('0', f->precision - (len - (f->sign ? 1 : 0)));
	if (f->field_len && !f->orient)
	{
		if (fl)
			write(1, "-", 1);
		ft_putchar_n(f->zerofill ? '0' : ' ', f->field_len - len);
		ft_putll_base_fd(n, 1, 10);
	}
	else if (f->orient)
	{
		ft_putll_base_fd(n, 1, 10);
		ft_putchar_n(' ', f->field_len - len);
	}
	else
		ft_putll_base_fd(n, 1, 10);
	if (f->field_len >= len)
		return (f->field_len);
	else if (f->ispre && f->precision > len)
		return (f->sign == 1 ? f->precision + 1 : f->precision);
	else
		return (len);
}