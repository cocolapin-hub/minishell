/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbrk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:46:24 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_strbrk(const char *s1, const char *s2)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		y = 0;
		while (s2[y])
		{
			if (s1[x] == s2[y])
				return (s2[y]);
			y++;
		}
		x++;
	}
	return (0);
}
