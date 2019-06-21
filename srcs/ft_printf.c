/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:10:55 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/21 20:05:28 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "libftprintf.h"
#include "libft.h"

char	*flag_parser(char *spec, t_frmt_fs *frmt)
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

char	*wp_parser(char *spec, t_frmt_fs *frmt, va_list arg)
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

int		type_mode(char *spec)
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

char	*type_parser(char *spec, t_frmt_fs *f)
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

char	*format_parser(char *spec, t_frmt_fs *frmt, va_list arg)
{
	ft_bzero(frmt, sizeof(t_frmt_fs));
	spec = flag_parser(spec, frmt);
	spec = wp_parser(spec, frmt, arg);
	spec = type_parser(spec, frmt);
	return (spec);
}

int		ft_printf(const char *format, ...)
{
	va_list				arg;
	size_t				n[2];
	char				*inputer[2];
	t_frmt_fs			frmt;

	va_start(arg, format);
	inputer[0] = (char *)format;
	n[1] = 0;
	while ((inputer[1] = ft_strchr(inputer[0], '%')))
	{
		write(1, inputer[0], (n[0] = inputer[1] - inputer[0]));
		n[1] += n[0];
		if (*(++inputer[1]) == '%' && ++n[1] && ++inputer[1])
			write(1, "%", 1);
		else
			inputer[1] = format_parser(inputer[1], &frmt, arg);
		inputer[0] = inputer[1];
	}
	n[0] = ft_strlen(inputer[0]);
	write(1, inputer[0], n[0]);
	va_end(arg);
	return ((int)(n[1] + n[0]));
}

/*
** fit : 0 -> Current format : 1-> END OF  format string : 2-> current buffer
*/
