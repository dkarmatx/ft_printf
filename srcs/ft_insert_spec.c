/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:53:55 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/21 20:59:32 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t		insert_spec(t_frmt_fs *frmt, va_list arg)
{
	if (frmt->type == 1)
		return (0);
	else if (frmt->type == 2)
		return (0);
	else if (frmt->type == 3)
		return (0);
	else if (frmt->type == 4)
		return (0);
	else if (frmt->type == 5)
		return (0);
	else
		return (0);
}
