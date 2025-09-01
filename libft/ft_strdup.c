/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:31:01 by claffut           #+#    #+#             */
/*   Updated: 2025/04/23 11:40:36 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*copy;

	i = 0;
	while (s[i])
		i++;
	copy = (char *)malloc(sizeof(char) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
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