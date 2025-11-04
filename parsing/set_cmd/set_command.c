/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:52:52 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	link_lst(t_command **cmd, t_shell *all, t_command	*new)
{
	if (!*cmd)
	{
		*cmd = new;
		all->cmd_head = *cmd;
	}
	else
		ft_lstadd_back_cmd(cmd, new);
}

t_command	*set_command(t_command **cmd, t_token *list, t_shell *all)
{
	t_command	*new;
	t_token		*elements;
	char		**args;

	while (list)
	{
		args = NULL;
		fill_args(list, &args);
		if (!args)
		{
			list = list->next;
			continue ;
		}
		fill_elements(&list, &elements);
		new = ft_lstnew_cmd(args, elements, all);
		if (!new)
			return (NULL);
		link_lst(cmd, all, new);
	}
	return (*cmd);
}
