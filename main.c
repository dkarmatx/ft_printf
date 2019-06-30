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

	ft_printf("%lld\n", -9223372036854775808);
	printf("%lld", -9223372036854775808);
}
