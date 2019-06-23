#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libftprintf.h"

int		main(void)
{
 printf(" <- %d\n", ft_printf("%08i", -71));
	printf(" <- %d\n", printf("%08i", -71));
 printf(" <- %d\n", ft_printf("%.0i", 0));
	printf(" <- %d\n", printf("%.0i", 0));
 printf(" <- %d\n", ft_printf("%-.12d", -1144));
	printf(" <- %d\n", printf("%-.12d", -1144));
 printf(" <- %d\n", ft_printf("%.5d", -421));
	printf(" <- %d\n", printf("%.5d", -421));
 printf(" <- %d\n", ft_printf("%d", -42));
	printf(" <- %d\n", printf("%d", -42));
 printf(" <- %d\n", ft_printf("%5d", -741));
	printf(" <- %d\n", printf("%5d", -741));


return (0);
}