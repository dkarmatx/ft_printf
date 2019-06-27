/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longnumber.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 11:52:11 by hgranule          #+#    #+#             */
/*   Updated: 2019/06/27 15:18:07 by hgranule         ###   ########.fr       */
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

#define LNUM_BYTES8 64

#define LINT_SIZE 278
#define LINT_OVER 1000000000000000000U

typedef struct			s_longnumber
{
	t_8b				mnt[LNUM_BYTES8];
	t_4b				exponent;
	t_1b				sign;
}						t_lnum;

typedef struct			s_bigint
{
	t_8b				num[LINT_SIZE + 2];
	t_1b				err;
}						t_bi;

long double		ln_to_ldouble(t_lnum lnum);
t_lnum			ln_multen_mnt(t_lnum n1);
t_lnum			ln_sub_mnt(t_lnum n1, t_lnum n2);
t_lnum			ln_summ_mnt(t_lnum n1, t_lnum n2);
int				ln_cmp(t_lnum n1, t_lnum n2);
int				ln_abscmp(t_lnum n1, t_lnum n2);
t_lnum			ln_lowshift(t_lnum num, t_4b shift);
t_lnum			ln_lowshift_mnt(t_lnum num, t_4b shift);
t_lnum			ln_from_ldouble(long double ldob);
t_8b			ln_to_ulong(t_lnum n);

#endif
// 9999999999990 999999834643759104
// 983330001231229998 552009649013260288
// 10003330001 231229999730655232