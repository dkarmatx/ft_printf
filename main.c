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
	test("%10%d %d", 10, 1);
	test("%%d %d", 10, 2);
	test("%-10%d %d", 10, 3);
	test("%0%d %d", 10, 4);
	test("%010%d %d", 10, 5);
	test("%d", 10, 6);
	ft_printf("%d  %d  %d\n", 1, 2, 3);
	printf("%d  %d  %d\n", 1, 2, 3);
}
