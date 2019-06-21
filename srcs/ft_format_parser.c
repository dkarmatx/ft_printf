/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:11:47 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/21 20:16:41 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*flag_parser(char *spec, t_frmt_fs *frmt)
{
	while (1)
	{
		if (*spec == '0')
			!frmt->orient ? frmt->zerofill = 1 : 0;
		else if (*spec == '+')
			frmt->sign = 1;
		else if (*spec == '-')
			frmt->orient = 1;
		else if (*spec == ' ')
			frmt->sign != 1 ? frmt->sign = 2 : 0;
		else if (*spec == '#')
			frmt->sharp = 1;
		else
			break ;
		++spec;
	}
	return (spec);
}

static char	*wp_parser(char *spec, t_frmt_fs *frmt, va_list arg)
{
	if (*spec == '*' && spec++)
		frmt->field_len = va_arg(arg, int);
	else if ((frmt->field_len = ft_atoi(spec)))
		while (ft_isdigit(*spec))
			spec++;
	if (*spec == '.')
	{
		frmt->ispre = 1;
		if (*(++spec) == '*' && spec++)
			frmt->precision = va_arg(arg, int);
		else if ((frmt->precision = ft_atoi(spec)))
			while (ft_isdigit(*spec))
				spec++;
	}
	return (spec);
}

static int	type_mode(char *spec)
{
	if (ft_memchr("dioxXu", (int)(*spec), 6))
		return (1);
	else if (ft_memchr("aAeEfFgG", (int)(*spec), 8))
		return (2);
	else if (*spec == 's')
		return (3);
	else if (*spec == 'c')
		return (4);
	else if (*spec == 'p')
		return (5);
	return (0);
}

static char	*type_parser(char *spec, t_frmt_fs *f)
{
	long double	m;

	f->size = 4;
	while (!(f->type = type_mode(spec)))
	{
		!(ft_strncmp("hh", spec, 2)) && f->size < sizeof(long)\
		? f->size = sizeof(char) : 0;
		*spec == 'h' && f->size < sizeof(long) && f->size > sizeof(char)\
		? f->size = sizeof(short) : 0;
		*spec == 'l' && f->size < sizeof(m) ? f->size = sizeof(long) : 0;
		!(ft_strncmp("ll", spec, 2)) && f->size < sizeof(m) \
		? f->size = sizeof(long long) : 0;
		*spec == 'z' && f->size < sizeof(m) ? f->size = sizeof(size_t) : 0;
		*spec == 't' && f->size < sizeof(m) ? f->size = sizeof(size_t) : 0;
		*spec == 'j' && f->size < sizeof(m) ? f->size = sizeof(size_t) : 0;
		*spec == 'L' ? f->size = sizeof(m) : 0;
		++spec;
	}
	f->type == 1 && f->size > 8 ? f->size = 8 : 0;
	f->type == 2 && !f->size ? f->size = 8 : 0;
	f->type == 2 && f->size < 8 ? f->size = 8 : 0;
	f->type == 3 || f->type == 5 ? f->size = 8 : 0;
	f->type == 4 ? f->size = 1 : 0;
	++spec;
	return (spec);
}

char		*format_parser(char *spec, t_frmt_fs *frmt, va_list arg)
{
	ft_bzero(frmt, sizeof(t_frmt_fs));
	spec = flag_parser(spec, frmt);
	spec = wp_parser(spec, frmt, arg);
	spec = type_parser(spec, frmt);
	return (spec);
}
