/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longnumber.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 11:52:11 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/22 11:57:41 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LONGNUMBER_H
# define LONGNUMBER_H

typedef unsigned long	t_8b;
typedef unsigned int	t_4b;
typedef unsigned char	t_1b;

#define LNUM_EXP_4SHIFT 0x7FFFFFFF

#define LDOUBLE_EXP_MASK 0x7FFF
#define LDOUBLE_EXP_SHIFT 0x3FFF

typedef struct			s_longnumber
{
	t_8b				mantissa[64];
	t_4b				exponent;
	t_1b				sign;
}						t_lnum;

#endif