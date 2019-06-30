/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_insertn_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:13:37 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/30 20:14:05 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					ft_return_insert_b(t_frmt_fs *f, int len)
{
	if (f->sharp && (f->spec == 'X' || f->spec == 'x') && f->precision > len)
		return (f->precision + 2);
	if (f->precision >= f->field_len && f->precision >= len)
		return (f->precision);
	else if (f->field_len > f->precision && f->field_len > len)
		return (f->field_len);
	else
		return (len);
	return (0);
}

int					ft_get_len_u(unsigned long long nb, int base, t_frmt_fs *f)
{
	int			rez;
	const int	spec_len = ft_parse_spec(f, 0, nb);

	rez = 0;
	if (nb == 0)
		++rez;
	if (f->sharp && nb != 0)
		rez += spec_len;
	while (nb > 0)
	{
		nb = nb / base;
		++rez;
	}
	return (rez);
}

int					ft_get_len(long long *n, int base, t_frmt_fs *f)
{
	int			rez;
	long long	cpy;

	if (ft_memchr("uUoOxX", (int)f->spec, 6))
		return (ft_get_len_u((*n), base, f));
	rez = 0;
	cpy = (*n);
	if ((*n) <= 0)
	{
		(*n) *= -1;
		cpy *= -1;
		++rez;
	}
	while (cpy > 0)
	{
		cpy = cpy / base;
		++rez;
	}
	if (f->sharp)
		if ((*n) != 0)
			rez += ft_parse_spec(f, 0, (*n));
	return (rez);
}

int					ft_kostyl_zero(t_frmt_fs *f, int len)
{
	(f->spec == 'O' || f->spec == 'o') ? ++len : 0;
	(f->orient && (f->spec == 'O' || f->spec == 'o')) ? write(1, "0", 1) : 0;
	ft_putchar_n(' ', f->field_len - (len - 1));
	(!f->orient && (f->spec == 'O' || f->spec == 'o')) ? write(1, "0", 1) : 0;
	return (ft_return_insert_b(f, len - 1));
}
