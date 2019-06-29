#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "libftprintf.h"
#include "longnumber.h"

t_lnum			ln_from_ldouble(long double ldob)
{
	t_lnum		lnm;
	t_8b		*bytedouble8;

	bytedouble8 = (t_8b *)&ldob;
	ft_bzero(&lnm, sizeof(lnm));
	lnm.sign = (bytedouble8[1] & 0x8000) >> 15;
	lnm.exponent = ((bytedouble8[1] & LDOUBLE_EXP_MASK)\
	- LDOUBLE_EXP_SHIFT) + LNUM_EXP_4SHIFT;
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
		return (1);
	else if (n2.exponent > n1.exponent)
		return (-1);
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
	return (sub);
}

t_lnum			ln_multint_mnt(t_lnum n1, t_8b ni)
{
	t_lnum	sum;

	ft_bzero(&sum, sizeof(sum));
	while (ni--)
		sum = ln_summ_mnt(sum, n1);
	return (sum);
}

t_8b			ln_to_ulong(const t_lnum n)
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

t_8b			ln_div(t_lnum n, t_lnum const d)
{
	t_8b	div;
	t_lnum	lzero;

	div = 0;
	ft_bzero(&lzero, sizeof(lzero));
	while (ln_cmp(n, d) >= 0)
	{
		++div;
		n = ln_sub(n, d);
	}
	return (div);
}

long double		ln_to_ldouble(const t_lnum lnum)
{
	long double		ldob;
	t_8b			*bytedouble8;

	bytedouble8 = (t_8b *)&ldob;
	bytedouble8[1] = 0x8000 & (lnum.sign << 15);
	bytedouble8[1] |= \
	((lnum.exponent - LNUM_EXP_4SHIFT + LDOUBLE_EXP_SHIFT) & LDOUBLE_EXP_MASK);
	bytedouble8[0] = lnum.mnt[LNUM_BYTES8 - 1];
	return (ldob);
}

char			*ln_string_fl_part(int prec, t_lnum lnum, char *over)
{
	t_8b		i;
	t_8b		j;
	char		*str;

	i = 0;
	str = ft_strnew(prec + 2);
	while (prec-- > -1)
	{
		lnum = ln_multint_mnt(ln_sub_mnt(lnum, \
		ln_from_ldouble((long double)ln_to_ulong(lnum))), 10);
		str[i++] = ln_to_ulong(lnum) + '0';
		str[i - 1] = str[i - 1] == '/' ? '0' : str[i - 1];
	}
	if (str[(j = --i)] >= '5')
	{
		while (i > 0 && str[--i] == '9')
			str[i] = '0';
		if (i > 0)
			++str[i];
		else
			*over = 1;
	}
	str[j] = 0;
	return (str);
}

t_bi			ln_pow_two(t_8b pow)
{
	t_bi		bi;
	int			i;

	ft_bzero(&bi, sizeof(bi));
	bi.num[0] = 1;
	while (pow--)
	{
		i = LINT_SIZE;
		while (--i > -1)
		{
			bi.num[i] <<= 1;
			if (bi.num[i] >= LINT_OVER)
			{
				bi.num[i] -= LINT_OVER;
				++bi.num[i + 1];
			}
		}
	}
	bi.num[LINT_SIZE] = 0;
	return (bi);
}

t_bi			ln_bint_add(t_bi a, t_bi b)
{
	t_bi		res;
	int			i;

	ft_bzero(&res, sizeof(res));
	i = -1;
	while (++i < LINT_SIZE)
	{
		res.num[i] += a.num[i] + b.num[i];
		if (res.num[i] >= LINT_OVER)
		{
			if (res.num[i] >= LINT_OVER)
				res.num[i] -= LINT_OVER;
			res.num[i + 1] = 1;
		}
	}
	res.num[LINT_SIZE] = 0;
	return (res);
}

t_bi			ln_get_bint(t_8b mnt, int exp)
{
	t_bi		bint;

	ft_bzero(&bint, sizeof(bint));
	while (exp > -1)
	{
		if (0x8000000000000000 & mnt)
			bint = ln_bint_add(bint, ln_pow_two(exp));
		mnt <<= 1;
		--exp;
	}
	return (bint);
}

t_bi			ln_get_t8byte(const long double ld)
{
	t_bi		bint;
	int			exp;
	t_8b const	*lp = (t_8b *)&ld;

	if ((LDOUBLE_EXP_MASK & lp[1]) >= LDOUBLE_EXP_SHIFT)
	{
		exp = (LDOUBLE_EXP_MASK & lp[1]) - LDOUBLE_EXP_SHIFT;
		bint = ln_get_bint(lp[0], exp);
	}
	else
		ft_bzero(&bint, sizeof(bint));
	return (bint);
}

char			*ln_n2s_rformat(size_t a, const int len,\
const char filler, char *st)
{
	int		ind;

	if (st)
	{
		ind = len;
		ft_memset(st, filler, len);
		st[ind] = 0;
		if (!a)
			st[ind - 1] = '0';
		while (a && --ind > -1)
		{
			st[ind] = (a % 10) + 48;
			a /= 10;
		}
		st[len] = 0;
	}
	return (st + len);
}

int inline		put_n_char(char c, ssize_t n)
{
	int		len;

	len = -1;
	while (++len < n)
	{
		write(1, &c, 1);
	}
	return (len);
}

char			*ln_string_int_part(long double ld, char over)
{
	t_bi			bint;
	const t_bi		bi1 = ln_get_bint(0x8000000000000000, 0);
	int				i;
	char			*str[2];
	size_t			len;

	i = LINT_SIZE;
	str[0] = ft_strnew(5000);
	bint = ln_get_t8byte(ld);
	if (over)
		bint = ln_bint_add(bint, bi1);
	while (bint.num[i] == 0 && i > 0)
		--i;
	str[1] = ft_lltoa_base(bint.num[i--], 10);
	len = ft_strlen(str[1]);
	ft_memcpy(str[0], str[1], len);
	free(str[1]);
	str[1] = str[0] + len;
	while (i > -1)
		str[1] = ln_n2s_rformat(bint.num[i--], 18, '0', str[1]);
	return (str[0]);
}

int	inline		put_float(t_frmt_fs *f, const char *fl, const char *fint, size_t len)
{
	if (!f->orient && !f->zerofill)
		len += put_n_char((f->zerofill ? '0' : ' '), f->field_len - len);
	if (f->error)
		write(1, "-", 1);
	else if (f->sign == 1)
		write(1, "+", 1);
	else if (f->sign == 2)
		write(1, " ", 1);
	if (!f->orient && f->zerofill)
		len += put_n_char((f->zerofill ? '0' : ' '), f->field_len - len);
	write(1, fint, ft_strlen(fint));
	if (f->ispre)
	{
		write(1, ".", 1);
		write(1, fl, ft_strlen(fl));
	}
	if (f->orient)
		len += put_n_char(' ', f->field_len - len);
	return (len);
}

size_t			print_spc_f(t_frmt_fs *f, const long double a)
{
	char		*str[2];
	char		over;
	size_t		len;

	over = 0;
	if (f->ispre)
		str[1] = ln_string_fl_part(f->precision, ln_from_ldouble(a), &over);
	else if (((long double)(a - (size_t)a) >= 0.5L && (size_t)a % 2) ||\
	((!(size_t)a % 2) && (long double)(a - (size_t)a) > 0.5L))
		over = 1;
	str[0] = ln_string_int_part(a, over);
	len = f->ispre ? f->precision + 1 : 0;
	len += ft_strlen(str[0]) + (a < 0 || f->sign > 0 ? 1 : 0);
	f->error = (a < 0);
	len = put_float(f, str[1], str[0], len);
	free(str[0]);
	free(str[1]);
	return (len);
}

int		main(void)
{
	long double a = 13232325234231231231231231231231232131231231231231233123123123123123123123231231231234234234242423423424234234234.99999L;
	size_t		b;
	t_frmt_fs	f;

	ft_bzero(&f, sizeof(f));
	f.sign = 1;
	f.ispre = 1;
	f.precision = 10;
	f.field_len = 2;
	f.zerofill = 0;
	f.orient = 0;
	b = print_spc_f(&f, a);
	b = printf("\n%LF\n", a);
	return (0);
}
