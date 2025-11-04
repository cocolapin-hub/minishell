/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:54:01 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*check_pipe(t_token *list, t_shell **all)
{
	if (list->type == PIPE && list->next == NULL)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		(*all)->last_status = 2;
		return (NULL);
	}
	if (list->type == PIPE
		&& (list->next->type != WORD || list->next->type != 0))
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		(*all)->last_status = 2;
		return (NULL);
	}
	return (list);
}
