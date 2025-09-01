/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:56:45 by claffut           #+#    #+#             */
/*   Updated: 2025/04/22 16:58:42 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	buffer1[20] = "Hello World!";
	char	buffer2[20] = "Hello World!";

	ft_memset(buffer1 + 6, '*', 5);

	memset(buffer2 + 6, '*', 5);

	printf("ft_memset : %s\n", buffer1);
	printf("memset    : %s\n", buffer2);

	return (0);
}
*/