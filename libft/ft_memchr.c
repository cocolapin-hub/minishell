/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:12:08 by claffut           #+#    #+#             */
/*   Updated: 2025/04/23 10:49:07 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char data[] = "Salut lol!";
	int c = 'l';
	size_t n = 5;

	void *res1 = ft_memchr(data, c, n);
	void *res2 = memchr(data, c, n);

	printf("ft_memchr : %s\n", res1 ? (char *)res1 : "NULL");
	printf("memchr    : %s\n", res2 ? (char *)res2 : "NULL");

	return 0;
}
*/