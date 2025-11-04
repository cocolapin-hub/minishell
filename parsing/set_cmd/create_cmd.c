/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:52:44 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	t_token	*find_target(t_token *tmp)
{
	t_token	*target;

	target = tmp->next;
	while (target && target->type == WORD && target->value[0] == '-')
		target = target->next;
	if (target && target->type == WORD)
		return (target);
	return (NULL);
}

static	t_token	*create_token_from(t_token *src)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = src->type;
	new->value = ft_strdup(src->value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->amount = src->amount;
	new->next = NULL;
	return (new);
}

void	create_cmd(t_token **tmp, t_token **new, t_token **start, t_token **end)
{
	t_token	*target;

	target = find_target(*tmp);
	if (!target)
		return ;
	*new = create_token_from(target);
	if (!*new)
		return ;
	if (!*start)
		*start = *new;
	else
		(*end)->next = *new;
	*end = *new;
	*tmp = target;
}

// void	create_cmd(t_token **tmp, t_token **new, t_token **start, t_token **end)
// {
// 	t_token	*target;

// 	target = (*tmp)->next;
// 	while (target && target->type == WORD && target->value[0] == '-')
// 		target = target->next;
// 	if (target && target->type == WORD)
// 	{
// 		*new = malloc(sizeof(t_token));
// 		if (!new)
// 			return ;
// 		(*new)->type = (*tmp)->type;
// 		(*new)->value = ft_strdup(target->value);
// 		if (!(*new)->value)
// 		{
// 			free(*new);
// 			*new = NULL;
// 			return ;
// 		}
// 		(*new)->amount = target->amount;
// 		(*new)->next = NULL;
// 		if (!(*start))
// 			*start = *new;
// 		else
// 			(*end)->next = *new;
// 		*end = *new;
// 		*tmp = target;
// 	}
// }
