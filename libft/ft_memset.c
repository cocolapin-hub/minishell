/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:32:15 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/10/03 17:18:51 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*word;

	i = 0;
	word = (unsigned char *)s;
	while (i < n)
	{
		word[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int	main(void)
{
	char *x = "it is a test";
	int y = 'x';
	size_t len = 5;
	printf("%s", (char *)ft_memset(&x, y , len));
}*/
