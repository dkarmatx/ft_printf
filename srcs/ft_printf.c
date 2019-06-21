/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:10:55 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/21 20:14:54 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

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
