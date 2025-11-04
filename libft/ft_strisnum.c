/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:46:42 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strisnum(const char *str)
{
	int	x;

	x = 0;
	if (str[x] == '+' || str[x] == '-')
		x++;
	if (!str[x])
		return (0);
	while (str[x])
	{
		if ((str[x] >= '0' && str[x] <= '9'))
			x++;
		else
			return (0);
	}
	return (1);
}
