#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "libftprintf.h"
#include "longnumber.h"


int inline		ft_putchar_n(char c, ssize_t n)
{
	int		len;

	len = -1;
	while (++len < n)
	{
		write(1, &c, 1);
	}
	return (len);
}

char			*ln_n2s_rformat(t_8b a, const int len,\
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

int		main(void)
{
	long double a = 13123212.51L;
	size_t		b;

	b = ft_printf("%.0Lf\n", a);
	b = printf("%.0Lf\n", a);
	return (0);
}
