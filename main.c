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
	lnm.mnt[LNUM_BYTES8 - 1] = bytedouble8[0];
	return (lnm);
}

t_lnum			ln_lowshift_mnt(t_lnum num, t_4b shift)
{
	t_8b		sup[LNUM_BYTES8 * 2];
	t_4b		bytes;
	t_4b		bits;
	int			i;

	shift %= LNUM_BYTES8 * 8 * 8;
	ft_bzero(sup, sizeof(sup));
	bytes = shift / 64;
	bits = shift % 64;
	ft_memcpy(&(sup[LNUM_BYTES8 - bytes]), num.mnt, LNUM_BYTES8 * 8);
	ft_memcpy(num.mnt, &(sup[LNUM_BYTES8]), LNUM_BYTES8 * 8);
	i = 0;
	while (i < LNUM_BYTES8)
	{
		sup[i + LNUM_BYTES8 - 1] = num.mnt[i] << (64 - bits);
		num.mnt[i] >>= bits;
		i++;
	}
	sup[LNUM_BYTES8 * 2 - 1] = 0;
	while (--i && shift)
		num.mnt[i] |= sup[i + LNUM_BYTES8];
	return (num);
}

t_lnum			ln_highshift_mnt(t_lnum num, t_4b shift)
{
	t_8b		sup[LNUM_BYTES8 * 2];
	t_4b		bytes;
	t_4b		bits;
	int			i;

	shift %= LNUM_BYTES8 * 8 * 8;
	ft_bzero(sup, sizeof(sup));
	bytes = shift / 64;
	bits = shift % 64;
	ft_memcpy(&(sup[bytes]), num.mnt, LNUM_BYTES8 * 8);
	ft_memcpy(num.mnt, &(sup[0]), LNUM_BYTES8 * 8);
	i = 0;
	while (i < LNUM_BYTES8)
	{
		sup[i + LNUM_BYTES8 + 1] = num.mnt[i] >> (64 - bits);
		num.mnt[i] <<= bits;
		i++;
	}
	sup[LNUM_BYTES8] = 0;
	while (--i && shift)
		num.mnt[i] |= sup[i + LNUM_BYTES8];
	return (num);
}

t_lnum			ln_lowshift(t_lnum num, t_4b shift)
{
	num.exponent += shift;
	num = ln_lowshift_mnt(num, shift);
	return (num);
}

t_lnum			ln_highshift(t_lnum num, t_4b shift)
{
	num.exponent -= shift;
	num = ln_highshift_mnt(num, shift);
	return (num);
}

int				ln_abscmp(t_lnum n1, t_lnum n2)
{
	int		i;

	if (n1.exponent > n2.exponent)
		n2 = ln_lowshift(n2, n1.exponent - n2.exponent);
	else if (n2.exponent > n1.exponent)
		n1 = ln_lowshift(n1, n2.exponent - n1.exponent);
	i = LNUM_BYTES8;
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
	(!n1.exponent ? n1.exponent = LNUM_EXP_4SHIFT : 0);
	(!n2.exponent ? n2.exponent = LNUM_EXP_4SHIFT : 0);
	if (!n1.exponent && !n2.exponent)
		return (0);
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
	while (++i < LNUM_BYTES8 - 1)
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
	if (((i = ln_cmp(n1, n2)) < 0))
		n1 = ln_lowshift(n1, n2.exponent - n1.exponent);
	else if (i > 0)
		n2 = ln_lowshift(n2, n1.exponent - n2.exponent);
	else
		return (ln_from_ldouble(0.0));
	ft_bzero(&sub, sizeof(sub));
	sub.exponent = n1.exponent;
	if (i < 0)
		sub.exponent = n2.exponent;
	i = 0;
	while (i < (LNUM_BYTES8 - 1))
	{
		sub.mnt[i] += n1.mnt[i] - n2.mnt[i];
		if (sub.mnt[i] > n1.mnt[i])
			--sub.mnt[i + i];
		++i;
	}
	sub.mnt[i] += n1.mnt[i] - n2.mnt[i];
	while (!(sub.mnt[LNUM_BYTES8 - 1] & 0x8000000000000000))
		sub = ln_highshift(sub, 1);
	return (sub);
}

t_lnum			ln_sub(t_lnum n1, t_lnum n2)
{
	t_lnum		sub;
	int			cp;

	ft_bzero(&sub, sizeof(sub));
	if (!n1.exponent && n2.exponent)
	{
		n2.sign = !n2.sign;
		return (n2);
	}
	else if (!n2.exponent)
		return (n1);
	if (((cp = ln_cmp(n1, n2)) > 0))
		sub = ln_sub_mnt(n1, n2);
	else if (cp < 0)
	{
		sub = ln_sub_mnt(n2, n1);
		sub.sign = !sub.sign;
	}
	return sub;
}

t_lnum			ln_multint_mnt(t_lnum n1, t_8b ni)
{
	t_lnum	sum;

	ft_bzero(&sum, sizeof(sum));
	while (ni--)
		sum = ln_summ_mnt(sum, n1);
	return (sum);
}

t_8b			ln_to_ulong(t_lnum n)
{
	t_8b			ulint;
	t_4b			bin_ds;

	bin_ds = 64 - (n.exponent - LNUM_EXP_4SHIFT + 1);
	ulint = n.mnt[LNUM_BYTES8 - 1];
	if (n.exponent > 63 + (t_4b)LNUM_EXP_4SHIFT)
		return ((t_8b)-1);
	if (n.exponent < LNUM_EXP_4SHIFT)
		return ((t_8b)0);
	ulint >>= bin_ds;
	return (ulint);
}

t_8b			ln_div(t_lnum n, t_lnum d)
{
	t_8b	div;
	t_lnum	lzero;
	long double		deb;

	div = 0;
	ft_bzero(&lzero, sizeof(lzero));
	while (ln_cmp(n, d) >= 0)
	{
		++div;
		n = ln_sub(n, d);
	}
	return (div);
}

long double		ln_to_ldouble(t_lnum lnum)
{
	long double		ldob;
	t_8b			*bytedouble8;

	bytedouble8 = (t_8b *)&ldob;
	bytedouble8[1] = 0x8000 & (lnum.sign << 15);
	bytedouble8[1] |= ((lnum.exponent - LNUM_EXP_4SHIFT + LDOUBLE_EXP_SHIFT) & LDOUBLE_EXP_MASK);
	bytedouble8[0] = lnum.mnt[LNUM_BYTES8 - 1];
	return (ldob);
}

char			*ln_print_fl_part(int prec, t_lnum lnum, char *over)
{
	t_8b		i;
	t_8b		j;
	char		*str;

	i = 0;
	str = ft_strnew(prec + 2);
	str[i++] = '.';
	*over = 0;
	while (prec-- > -1)
	{
		lnum = ln_multint_mnt(ln_sub_mnt(lnum, \
		ln_from_ldouble((long double)ln_to_ulong(lnum))), 10);
		str[i++] = ln_to_ulong(lnum) + '0';
	}
	if (str[(j = --i)] >= '5')
	{
		while (str[--i] == '9')
			str[i] = '0';
		if (i > 1)
			++str[i];
		else
			*over = 1;
	}
	str[j] = 0;
	return (str);
}

int		main(void)
{
	long double		a = 0.11112312311;
	long double		b = 6.999999;
	char			ov;
	char			*str;

	t_lnum		la = ln_from_ldouble(a);
	t_lnum		lb = ln_from_ldouble(b);

	str = ln_print_fl_part(30, lb, &ov);
	ft_putstr(str);
	printf("\n%.30LF", b);

	b = ln_to_ldouble(lb);
	return (0);
}
