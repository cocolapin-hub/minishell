/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:31:01 by claffut           #+#    #+#             */
/*   Updated: 2025/09/11 10:47:24 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s, int x, int len)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		exit (1);
	i = 0;
	while (len != 0)
	{
		copy[i++] = s[x++];
		len--;
	}
	copy[i] = '\0';
	return (copy);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char *src = "Salut les copains !";

	char *dup1 = ft_strdup(src);
	char *dup2 = strdup(src);

	printf("ft_strdup : %s\n", dup1);
	printf("strdup    : %s\n", dup2);

	free(dup1);
	free(dup2);

	return 0;
}
*/