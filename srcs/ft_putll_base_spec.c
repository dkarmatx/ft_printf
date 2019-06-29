/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putll_base_spec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:35:23 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/29 21:01:18 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

long long	get_max_dec(long long nb, int base, char spec)
{
	long long			dec;

	dec = 1;
	nb < 0 ? nb *= -1 : nb;
	while ((dec * base < nb) && (dec * base > 0))
		dec *= base;
	return (dec);
}

unsigned long long	get_max_dec_u(unsigned long long nb, int base, char spec)
{
	size_t			dec;

	dec = 1;
	while ((dec * base < nb) && dec < dec * base && (dec * base > 0))
		dec *= base;
	return (dec);
}

int			ft_get_base(char c)
{
	if (c == 'o' || c == 'O')
		return (8);
	if (c == 'x' || c == 'X')
		return (16);
	return (10);
}

void		ft_putull_base_spec(unsigned long long nb, char spec)				
{
	unsigned long long		dec;
	int						cur;
	char					*alphU;
	char					*alph;
	int						base;

	alphU = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
	alph = "0123456789abcdefghijklmnopqrstuv";
	base = ft_get_base(spec);
	dec = get_max_dec_u(nb, base, spec);
	while (dec > 0)
	{
		if ((cur = nb / dec) == base)
			write(1, "10", 2);
		else
			write(1, spec == 'X' ? &(alphU[cur]) : &(alph[cur]), 1);
		nb %= dec;
		dec /= base;
	}
}

void				ft_putll_base_spec(long long nb, char spec)
{
	long long		dec;
	int				cur;
	char			*alphU;
	char			*alph;
	int				base;

	alphU = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
	alph = "0123456789abcdefghijklmnopqrstuv";
	base = ft_get_base(spec);
	dec = get_max_dec(nb, base, spec);
	if (!ft_memchr("uUoOxX", spec, 6))
	{
		// if (nb < 0)
		// {
		// 	nb *= -1;
		// 	write(1, "-", 1);
		// }
		while (dec > 0)
		{
			if ((cur = nb / dec) == base)
				write(1, "10", 2);
			else
				write(1, spec == 'X' ? &(alphU[cur]) : &(alph[cur]), 1);
			nb %= dec;
			dec /= base;
		}
	}
	else
		ft_putull_base_spec(nb, spec);
}
