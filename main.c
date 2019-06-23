#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libftprintf.h"

int		main(void)
{
 printf(" <- %d\n", ft_printf("%-8s", "coco"));
	printf(" <- %d\n", printf("%-8s", "coco"));
//  printf(" <- %d\n", ft_printf("%10.15s", "coco"));
// 	printf(" <- %d\n", printf("%10.15s", "coco"));
//  printf(" <- %d\n", ft_printf("Svoi_str -> %*.*c", 2, 0, 's'));
// 	printf(" <- %d\n", printf("Orig_str -> %*.*c", 2, 0, 's'));
// 	printf(" <- %d\n", printf("Orig_str -> %10s", "www"));
//  printf(" <- %d\n", ft_printf("Svoi_str -> %10s", "www"));

return (0);
}