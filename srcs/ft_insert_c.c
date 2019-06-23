/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 01:30:42 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/06/23 10:56:45 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int			ft_insert_c(t_frmt_fs *f, va_list arg)
{
	char	c;
	size_t	size;
	
	size = f->field_len;
	c = va_arg(arg, int);
	if (!f->orient)
	{
		ft_putchar_n(f->zerofill ? '0' : ' ', size - 1);
		write(1, &c, 1);
	}
	else
	{
		write(1, &c, 1);
		ft_putchar_n(f->zerofill ? '0' : ' ', size - 1);
	}
	return (size ? size : 1);
}