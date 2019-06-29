#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libftprintf.h"

int		main(void)
{
	printf(" <-- %d\n", ft_printf("coco et %-#-#--24O titi%#012o", 12, -874));
	printf(" <-- %d\n", printf("coco et %-#-#--24O titi%#012o", 12, -874));
	// printf(" <-- %d\n", ft_printf("%hho", (unsigned char)-12));
	// printf(" <-- %d\n", printf("%hho", (unsigned char)-12));
	// printf(" <-- %d\n", ft_printf("%-12o", 01423));
	// printf(" <-- %d\n", printf("%-12o", 01423));
return (0);
}