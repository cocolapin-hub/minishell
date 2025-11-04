/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:45:16 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*tmp;
	size_t		total;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb > (SIZE_MAX / size) && size != 0)
		return (NULL);
	total = nmemb * size;
	tmp = (char *)malloc(total);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, total);
	return (tmp);
}
/*
#include <stdio.h>
#include <limits.h>
int main()
{
	char *test;

	test = NULL;
	test = ft_calloc(4294967295, 4294967295);
	// printf("%s\n", test);
	return 0;
}*/
