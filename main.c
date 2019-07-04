/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:21:33 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/07/04 17:24:10 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include "libft.h"
# include "longnumber.h"
# include "libftprintf.h"


int main()
{
	unsigned long long ULLONG_MAX = +18446744073709551615;
	printf("<-- %d\n", ft_printf("%-#--.0---0-m--{};,;;[];;;y-----[ld"), 10);
	printf("<-- %d\n", printf("%-#-.0---000m---};;,;;;[];;y-----[ld"), 10);
}