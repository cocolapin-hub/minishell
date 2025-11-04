/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:44:26 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_new_var(t_local **env, char *key, char *value)
{
	t_local	*new;

	new = malloc(sizeof(t_local));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), (void)0);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = *env;
	*env = new;
}

void	set_env_value(t_local **env, char *key, char *value)
{
	t_local	*node;

	node = find_env_key(*env, key);
	if (node)
	{
		if (node->value)
		{
			free(node->value);
			node->value = NULL;
		}
		if (value)
			node->value = ft_strdup(value);
		return ;
	}
	add_new_var(env, key, value);
}
