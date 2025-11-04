/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:55:34 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_elements(t_token **list, t_token **elements)
{
	t_token	*start;
	t_token	*tmp;
	t_token	*end;
	t_token	*new;

	start = NULL;
	tmp = *list;
	end = NULL;
	new = NULL;
	if (!(*list) || !list)
	{
		*elements = NULL;
		return ;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type != PIPE && tmp->type != WORD)
			create_cmd(&tmp, &new, &start, &end);
		tmp = tmp->next;
	}
	*elements = start;
	if (tmp && tmp->type == PIPE)
		*list = tmp->next;
	else
		*list = tmp;
}

/*
void	fill_elements(t_token **list, t_token **elements)
{
	t_token	*start;
	t_token	*tmp;
	t_token	*end;
	t_token	*new;

	start = NULL;
	tmp = *list;
	end = NULL;
	new = NULL;
	if (!(*list) || !list)
	{
		*elements = NULL;
		return ;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			create_cmd(&tmp, &new, &start, &end);
		tmp = tmp->next;
	}
	*elements = start;
	if (tmp && tmp->type == PIPE)
		*list = tmp->next;
	else
		*list = tmp;
}*/