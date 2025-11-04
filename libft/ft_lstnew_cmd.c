/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:45:49 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*ft_lstnew_cmd(char **args, t_token *elements, t_shell *all)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = args;
	node->elem = elements;
	node->all = all;
	node->next = NULL;
	return (node);
}
/*
	if (!node)
		exit (1); //--> end code;

	//malloc and give all args
	node->args = args;

	//all nodes withing the cmd
	node->elem = elements;

	//the same env
	node->all = all;

	//pointer to next
	node->next = NULL;
*/