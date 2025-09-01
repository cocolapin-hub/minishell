/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:54:25 by claffut           #+#    #+#             */
/*   Updated: 2025/04/23 10:31:56 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char *s1 = "CoucouA";
	const char *s2 = "CoucouC";

	size_t n = 7;

	int res1 = ft_strncmp(s1, s2, n);
	int res2 = strncmp(s1, s2, n);

	printf("ft_strncmp : %d\n", res1);
	printf("strncmp    : %d\n", res2);

	return 0;
}
*/