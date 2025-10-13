/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbrk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:37:09 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/10/13 12:18:31 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_strbrk(const char *s1, const char *s2)
{
	int x = 0;
	int y = 0;

	while(s1[x])
	{
		y = 0;
		while(s2[y])
		{
			if (s1[x] == s2[y])
				return (s2[y]);
			y++;
		}
		x++;
	}
	return (0);
}