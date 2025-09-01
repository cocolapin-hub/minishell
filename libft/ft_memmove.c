/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:01:20 by claffut           #+#    #+#             */
/*   Updated: 2025/04/22 18:53:04 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	forward_copy(unsigned char *d, const unsigned char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
}

static void	backward_copy(unsigned char *d, const unsigned char *s, size_t len)
{
	while (len > 0)
	{
		len--;
		d[len] = s[len];
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d < s)
		forward_copy(d, s, len);
	else
		backward_copy(d, s, len);
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char buffer1[30] = "123456";
	char buffer2[30] = "123456";

	ft_memmove(buffer1 + 1, buffer1, 4); // backward_copy
	memmove(buffer2 + 1, buffer2, 4);

	ft_memmove(buffer1, buffer1 + 2, 4); // forward_copy
	memmove(buffer2, buffer2 + 2, 4);

	printf("ft_memmove : %s\n", buffer1);
	printf("memmove    : %s\n", buffer2);

	return (0);
}
*/