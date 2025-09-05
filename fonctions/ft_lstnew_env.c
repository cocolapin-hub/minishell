/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:39:27 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/05 16:34:25 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_local	*ft_lstnew_env(char *value, char *key)
{
	t_local	*node;

	node = malloc(sizeof(t_local));
	if (!node)
		exit (1);

	node->value = value;
	node->key = key;
	node->next = NULL;
	return (node);
}