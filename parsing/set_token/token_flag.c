/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/05 19:02:06 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	token_flag_off(char *cmd, int quote, t_token **list)
{
	char	**split;
	t_token	*new;
	int		i;

	split = ft_split(cmd, ' ');
	if (!split)
		return (free(cmd));
	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) > 0)
		{
			new = ft_lstnew_token(split[i], quote);
			if (!new)
				return (free_split(split), free(cmd));
			if (!*list)
				*list = new;
			else
				ft_lstadd_back(list, new);
		}
		free(split[i]);
		i++;
	}
	free(split);
	free(cmd);
}

void	token_flag_on(char *cmd, int quote, t_token **list)
{
	t_token	*new;

	new = ft_lstnew_token(cmd, quote);
	if (!new)
	{
		free(cmd);
		return ;
	}
	if (!*list)
		*list = new;
	else
		ft_lstadd_back(list, new);
	free(cmd);
}
