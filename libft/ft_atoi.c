/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:38:21 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/10/08 15:55:06 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	edge(const char *str, unsigned long result, int i, int flag)
{
	size_t	x;

	x = i;
	while (str[x] >= 48 && str[x] <= 57)
	{
		if (result > 2147483647 && flag == 1)
			return (0);
		if (result > 2147483648 && flag == -1)
			return (0);
		result = result * 10 + (str[x] - '0');
		x++;
	}
	return (result);
}

int	ft_atoi(const char *nptr)
{
	size_t	result;
	size_t	x;
	int		flag;

	flag = 1;
	x = 0;
	while (nptr[x] == 32 || (nptr[x] >= 9 && nptr[x] <= 13))
		x++;
	if (nptr[x] == 45 || nptr[x] == 43)
	{
		if (nptr[x] == 45)
			flag *= -1;
		x++;
	}
	if (nptr[x] == 45 || nptr[x] == 43)
		return (0);
	result = 0;
	result = edge(nptr, result, x, flag);
	return ((int) result * flag);
}
/*
#include <stdlib.h>
#include <stdio.h>
int main(void)
{

int result= ft_atoi("   +56");
printf("%d ==>%d", result, atoi("   ++56"));


}
*/
