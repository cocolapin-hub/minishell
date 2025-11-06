/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 20:48:48 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_args(t_token *list, int token_count, int skip, char ***args)
{
	t_token	*tmp;

	tmp = list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			skip = 1;
		else if (tmp->type == WORD)
		{
			if (skip)
				skip = 0;
			else
				token_count++;
		}
		tmp = tmp->next;
	}
	*args = ft_calloc(token_count + 1, sizeof(char *));
	if (!(*args))
		*args = NULL;
	else
		(*args)[token_count] = 0;
}
