/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:53:35 by claffut           #+#    #+#             */
/*   Updated: 2025/08/04 15:59:28 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total;
	size_t			i;
	unsigned char	*ptr;

	total = count * size;
	if (count != 0 && total / count != size)
		return (NULL);
	ptr = (unsigned char *)malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
		ptr[i++] = 0;
	return ((void *)ptr);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int *ptr1 = ft_calloc(3, sizeof(int));
	int *ptr2 = calloc(3, sizeof(int));

	printf("ft_calloc : %d %d %d\n", ptr1[0], ptr1[1], ptr1[2]);
	printf("calloc    : %d %d %d\n", ptr2[0], ptr2[1], ptr2[2]);

	free(ptr1);
	free(ptr2);

	return 0;
}
*/