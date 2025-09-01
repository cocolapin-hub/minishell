/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:40:44 by claffut           #+#    #+#             */
/*   Updated: 2025/04/23 11:21:07 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	const char *tests[] = {
		"42",
		"   -123",
		"+987",
		"  -42truc",
		"hello",
		"-2147483648",
		NULL
	};

	for (int i = 0; tests[i]; i++)
	{
		int res1 = ft_atoi(tests[i]);
		int res2 = atoi(tests[i]);
		printf("%s: ft_atoi = %d | atoi = %d\n", tests[i], res1, res2);
	}

	return 0;
}
*/