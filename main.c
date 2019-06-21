#include <stdio.h>
#include <stdlib.h>
#include "libftprintf.h"

int		main(void)
{
	printf(" <- %d\n", ft_printf("a%dbcd", 14));
	printf(" <- %d\n", ft_printf("a%lldbcd", 14));
	printf(" <- %d\n", ft_printf("a%llll-0lllllllllhhhllbcd", 14));
	printf(" <- %d\n", ft_printf("%zu", 14));
	printf(" <- %d\n", ft_printf("%f", 14));
	printf(" <- %d\n", ft_printf("%c", 14));
	return (0);
}