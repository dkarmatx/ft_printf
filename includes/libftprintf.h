/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:02:48 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/21 20:05:16 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

/*
** bufflen - Размер буфера вывода для int. для float количество символов слева
** prelen - точность
** base - система счисления
** orient - если 0 то выравнивание по правому краю иначе по левому
** zerofill - заполнение 0 или нет
** asteriks - если 0b00 x.x, если 0b10 *.x, если 0b01 x.*, 0b11 *.*
** sharp - # ? 1 : 0
** sign - требуется вывод знака или нет
*/
typedef struct		s_flags_specifier
{
	int				error;
	int				type;
	int				size;
	int				field_len;
	int				precision;
	char			base;
	char			orient;
	char			zerofill;
	char			asteriks;
	char			sharp;
	char			sign;
	char			ispre;
}					t_frmt_fs;

int			ft_printf(const char *format, ...);

#endif