/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:41:18 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/16 11:40:22 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*ft_lstnew_cmd(char **args, t_token **list, t_SHELL *all)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		exit (1); //--> end code;

	//malloc and give all args
	node->args = args;

	/*the right t_token*/
	node->element = *list;
	*list = (*list)->next;

	/*the same env*/
	node->all = all;

	/*pointer to next*/
	node->next = NULL;

	return(node);
}
