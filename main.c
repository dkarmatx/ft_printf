#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libftprintf.h"
#include "longnumber.h"

#define test(str, value, n) printf("\n==================| %d test |==================\n", n); \
							printf(" <-- %d\n", ft_printf(str, value)); \
							printf(" <-- %d\n", printf(str, value));

int		main(void)
{
	double a = 0;
	t_8b b = 0xfff0000000000000;

	memcpy(&a, &b, 8);
	test("%f", a, 1);

	b = 0x7ff0000000000000;
	memcpy(&a, &b, 8);
	test("%f", a, 2);

	b = 0xfff0100000000000;
	memcpy(&a, &b, 8);
	test("%f", a, 3);

	b = 0x7ff0010000000000;
	memcpy(&a, &b, 8);
	test("%F", a, 4);

	b = 0xfff0000000000000;
	memcpy(&a, &b, 8);
	test("%F", a, 5);

	b = 0x7ff0000000000000;
	memcpy(&a, &b, 8);
	test("%F", a, 6);

	b = 0x7ff0000110000000;
	memcpy(&a, &b, 8);
	test("%f", a, 7);

	b = 0xfff0000001000000;
	memcpy(&a, &b, 8);
	test("%F", a, 8);
}
