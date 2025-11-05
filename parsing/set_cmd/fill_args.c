/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/05 11:14:17 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_args(t_token *list, char ***args)
{
	int		skip;
	int		x;

	create_args(list, 0, 0, args);
	skip = 0;
	x = 0;
	while (*args && list && list->type != PIPE)
	{
		if (list->type == REDIR_IN || list->type == REDIR_OUT
			|| list->type == REDIR_APPEND || list->type == REDIR_HEREDOC)
			skip = 1;
		else if (list->type == WORD)
		{
			if (skip == 1 && ft_strcmp(list->value, "-n"))
				skip = 0;
			else
				(*args)[x++] = ft_strdup(list->value);
		}
		list = list->next;
	}
}
