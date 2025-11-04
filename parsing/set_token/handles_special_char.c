/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_special_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:53:33 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handles_special_char(char *line, int x, t_token **list)
{
	t_token	*new;
	char	*cmd;
	int		y;

	cmd = NULL;
	y = x;
	if (line[x] == 124)
		cmd = ft_strdup_m(line, x, 1);
	else if (line[x] == 60 || line[x] == 62)
	{
		if (line[x + 1] == line[x])
		{
			cmd = ft_strdup_m(line, x, 2);
			y++;
		}
		else
			cmd = ft_strdup_m(line, x, 1);
	}
	new = ft_lstnew_token(cmd, 0);
	if (!*list)
		*list = new;
	else
		ft_lstadd_back(list, new);
	return (y + 1);
}
