#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libftprintf.h"
#include "longnumber.h"

t_lnum			ln_from_ldouble(long double ldob)
{
	t_lnum		lnm;
	t_8b		*bytedouble8;

	bytedouble8 = (t_8b *)&ldob;
	ft_bzero(&lnm, sizeof(lnm));
	lnm.sign = (bytedouble8[1] & 0x8000) >> 15;
	lnm.exponent = ((bytedouble8[1] & LDOUBLE_EXP_MASK) - LDOUBLE_EXP_SHIFT) + LNUM_EXP_4SHIFT;
	lnm.mnt[63] = bytedouble8[0];
	return (lnm);
}

t_lnum			ln_lowshift_mnt(t_lnum num, t_4b shift)
{
	t_8b		sup[128];
	t_4b		bytes;
	t_4b		bits;
	int			i;

	shift %= 4096;
	ft_bzero(sup, sizeof(sup));
	bytes = shift / 64;
	bits = shift % 64;
	i = 64;
	ft_memcpy(&(sup[64 - bytes]), num.mnt, 512);
	ft_memcpy(num.mnt, &(sup[64]), 512);
	sup[1] = 0;
	while (i--)
	{
		num.mnt[i] |= sup[1];
		sup[0] = num.mnt[i];
		sup[1] = sup[0] << (8 - bits);
		num.mnt[i] >>= bits;
	}
	return (num);
}

t_lnum			ln_lowshift(t_lnum num, t_4b shift)
{
	num.exponent += shift;
	num = ln_lowshift_mnt(num, shift);
	return (num);
}

int				ln_abscmp(t_lnum n1, t_lnum n2)
{
	int		i;

	if (n1.exponent > n2.exponent)
		n2 = ln_lowshift(n2, n1.exponent - n2.exponent);
	else if (n2.exponent > n1.exponent)
		n1 = ln_lowshift(n1, n2.exponent - n1.exponent);
	i = 64;
	while (i--)
	{
		if (n1.mnt[i] > n2.mnt[i])
			return (1);
		if (n2.mnt[i] > n1.mnt[i])
			return (-1);
	}
	return (0);
}

int				ln_cmp(t_lnum n1, t_lnum n2)
{
	if (n1.sign == n2.sign)
	{
		if (!n1.sign)
			return (ln_abscmp(n1, n2));
		else
			return (-1 * ln_abscmp(n1, n2));
	}
	else
	{
		if (n1.sign > n2.sign)
			return (-1);
		else
			return (1);
	}
}

t_lnum			ln_summ_mnt(t_lnum n1, t_lnum n2)
{
	int			i;
	t_lnum		sum;

	ft_bzero(&sum, sizeof(sum));
	if (n1.exponent > n2.exponent)
		n2 = ln_lowshift(n2, n1.exponent - n2.exponent);
	else if (n2.exponent > n1.exponent)
		n1 = ln_lowshift(n1, n2.exponent - n1.exponent);
	i = -1;
	sum.exponent = n1.exponent;
	while (++i < 63)
	{
		sum.mnt[i] += n1.mnt[i] + n2.mnt[i];
		if ((sum.mnt[i] < n1.mnt[i]) || (sum.mnt[i] < n2.mnt[i]))
			++sum.mnt[i + 1];
	}
	sum.mnt[i] += n1.mnt[i] + n2.mnt[i];
	if ((sum.mnt[i] < n1.mnt[i]) || (sum.mnt[i] < n2.mnt[i]))
	{
		sum = ln_lowshift(sum, 1);
		sum.mnt[i] += 0x8000000000000000;
	}
	return (sum);
}

t_lnum			ln_sub_mnt(t_lnum n1, t_lnum n2)
{
	int			i;
	t_lnum		sub;
	char		sign;

	sign = 0;
	if (ln_cmp(n1, n2) < 0)
	{
		sub = n1;
		n1 = n2;
		n2 = sub;
		sign = !sign;
	}
	n2 = ln_lowshift(n2, n1.exponent - n2.exponent);
	ft_bzero(&sub, sizeof(sub));
	sub.exponent = n1.exponent;
	i = 0;
	while (++i < 63)
	{
		sub.mnt[i] += n1.mnt[i] - n2.mnt[i];
		if (sub.mnt[i] > n1.mnt[i])
			--sub.mnt[i + 1];
	}
	sub.mnt[i] += n1.mnt[i] - n2.mnt[i];
	if (sub.mnt[i] > n1.mnt[i])
		sub = ln_lowshift(sub, 1);
	sub.sign = sign;
	return (sub);
}

t_lnum			ln_multen_mnt(t_lnum n1)
{
	int		i;
	t_lnum	sum;

	i = 10;
	ft_bzero(&sum, sizeof(sum));
	while (i--)
		sum = ln_summ_mnt(sum, n1);
	return (sum);
}

long double		ln_to_ldouble(t_lnum lnum)
{
	long double		ldob;
	t_8b			*bytedouble8;

	bytedouble8 = (t_8b *)&ldob;
	bytedouble8[1] = 0x8000 & (lnum.sign << 15);
	bytedouble8[1] |= ((lnum.exponent - LNUM_EXP_4SHIFT + LDOUBLE_EXP_SHIFT) & LDOUBLE_EXP_MASK);
	bytedouble8[0] = lnum.mnt[63];
	return (ldob);
}

// int		main(void)
// {
// 	t_lnum		ln1 = ln_from_ldouble(0.33333333333333);
// 	ln1 = ln_multen_mnt(ln1);
// 	ln1 = ln_multen_mnt(ln1);
// 	ln1 = ln_multen_mnt(ln1);
// 	ln1 = ln_multen_mnt(ln1);
// 	long double	ld1 = ln_to_ldouble(ln1);
// 	return (0);
// }
