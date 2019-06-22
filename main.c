#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libftprintf.h"
#include "longnumber.h"

t_lnum		ln_from_ldouble(long double ldob)
{
	t_lnum		lnm;
	t_8b		*bytedouble8;

	bytedouble8 = (t_8b *)&ldob;
	ft_bzero(&lnm, sizeof(lnm));
	lnm.sign = (bytedouble8[1] & 0x8000) >> 15;
	lnm.exponent = ((bytedouble8[1] & LDOUBLE_EXP_MASK) - LDOUBLE_EXP_SHIFT) + LNUM_EXP_4SHIFT;
	lnm.mantissa[63] = bytedouble8[0];
	return (lnm);
}

t_lnum		ln_lowshift_mnt(t_lnum num, t_4b shift)
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
	ft_memcpy(&(sup[64 - bytes]), num.mantissa, 512);
	ft_memcpy(num.mantissa, &(sup[64]), 512);
	sup[1] = 0;
	while (i--)
	{
		num.mantissa[i] |= sup[1];
		sup[0] = num.mantissa[i];
		sup[1] = sup[0] << (8 - bits);
		num.mantissa[i] >>= bits;
	}
	return (num);
}

int		main(void)
{
	t_lnum a = ln_from_ldouble(5.0);
	a = ln_lowshift_mnt(a, 65);
	return (0);
}
