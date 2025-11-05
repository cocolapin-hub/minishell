/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_after_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/05 18:40:15 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*clean_after_expansion(char *str)
{
	char	*new_line;
	int		len;
	int		x;
	int		y;

	len = ft_strlen(str);
	new_line = malloc(sizeof(char) * len + 1);
	if (!new_line)
		return (NULL);
	y = 0;
	x = 0;
	while (str[x])
	{
		if ((x != 0 && str[x] == 32 && str[x - 1] == 32)
			|| (x != 0 && str[x] == 9 && str[x - 1] == 9))
			x++;
		else
			new_line[y++] = str[x++];
	}
	new_line[y] = '\0';
	return (new_line);
}
