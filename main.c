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
	int strlen;

	printf("<%d\n" , ft_printf("%f|%f", 1.0, 1.0));
	printf("<%d\n" , printf("%.2147483649f|%2147483649f", 1.0, 1.0));
}

//0.000000|0.000000|+0.000000| 0.000000|0.000000|0.000000<55
//0.000000|0.000000|+0.000000| 0.000000|0.000000|0.000000<55