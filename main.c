#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libftprintf.h"

#define test(str, value, n) printf("\n==================| %d test |==================\n", n); \
							printf(" <-- %d\n", ft_printf(str, value)); \
							printf(" <-- %d\n", printf(str, value));

int		main(void)
{
	int ret;
	int tret;

	test("%------------7i", 0xd777, 1);
	test("%000000000000007d", 0x45, 2);
	test("%ls", L"„Äª", 3);
}