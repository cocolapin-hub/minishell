/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/05 10:59:55 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_cmd(t_token **tmp, t_token **new, t_token **start, t_token **end)
{
	t_token	*target;

	target = (*tmp)->next;
	while (target && target->type == WORD && target->value[0] == '-')
		target = target->next;
	if (target && target->type == WORD)
	{
		*new = malloc(sizeof(t_token));
		(*new)->type = (*tmp)->type;
		(*new)->value = ft_strdup(target->value);
		if (!(*new)->value)
		{
			free(*new);
			*new = NULL;
			return ;
		}
		(*new)->amount = target->amount;
		(*new)->next = NULL;
		if (!(*start))
			*start = *new;
		else
			(*end)->next = *new;
		*end = *new;
		*tmp = target;
	}
}
