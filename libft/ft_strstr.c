/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:46:57 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (big[i])
	{
		j = 0;
		while (little[j] && big[i + j] == little[j])
			j++;
		if (!little[j])
			return (i);
		i++;
	}
	return (-1);
}
/*
#include <stdio.h>

int	main(void)
{
	const char big[] = "Hello les biches";
	const char little[] = "les";
	size_t len = 10;

	char *res1 = ft_strnstr(big, little, len);

	printf("ft_strnstr : %s\n", res1 ? res1 : "NULL");

	return 0;
}
*/