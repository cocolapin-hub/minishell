/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:46:39 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	x;

	dst = (char *)malloc(ft_strlen(s) + 1);
	if (!dst)
		return (NULL);
	x = 0;
	while (s[x])
	{
		dst[x] = s[x];
		x++;
	}
	dst[x] = 0;
	return (dst);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s", ft_strdup("mari"));


}*/
