/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 19:08:41 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*tokenisation(int x, char *line, t_token **list, t_shell **all)
{
	while (line[x])
	{
		while (line[x] == 32 || line[x] == 9)
			x++;
		if (line[x] == '\0')
			break ;
		if (line[x] == '|' || line[x] == '<' || line[x] == '>')
			x = handles_special_char(line, x, list);
		else
		{
			x = handles_command(line, x, list, all);
			if (x == -1)
			{
				free_tokens(*list);
				*list = NULL;
				return (NULL);
			}
		}
	}
	if (!*list)
		return (NULL);
	return (*list);
}
