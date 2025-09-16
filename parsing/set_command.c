/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:41:18 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/16 15:17:41 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_args(t_token *list, char ***args)
{
	int 	token_count;
	t_token	*tmp;
	int		x;

	token_count = 0;
	tmp = list;
	x = 0;

	/*count len with a tmp*/
	while (tmp && tmp->type == WORD)
	{
		token_count++;
		tmp = tmp->next;
	}

	/*creates args */
	*args = malloc(sizeof(char *) * (token_count + 1));
	if (!(*args))
		exit (1); 						//--> end code propery later;
	(*args)[token_count] = 0;

	/*allocate value*/
	while (list && list->type == WORD)
	{
		(*args)[x++] = ft_strdup(list->value);
		list = list->next;
	}

	//lst modifications are constrained here
}

void	fill_elements(t_token **list, t_token **elements)
{
	t_token	*start;
	t_token	*end;

	if (!(*list) || !list)
	{
		*elements = NULL;
		return ;
	}

	start = *list;
	end = *list;

	/*place end*/
	while(end && end->type != PIPE)
		end = end->next;

	/*set list & set start*/
	*elements = start;
	if (end)
	{
		*list = end->next;
		end->next = NULL;
	}
	else
		*list = NULL;
}

void	set_command(t_command **cmd, t_token *list, t_SHELL *all)
{
	t_command	*new;
	t_token		*elements;
	char 		**args;

	while(list)
	{
		fill_args(list, &args);
		fill_elements(&list, &elements);

		new = ft_lstnew_cmd(args, elements, all);
		if (!*cmd)
			*cmd = new;
		else
			ft_lstadd_back_cmd(cmd, new);
	}
}


/*
EXEMPLE:

cmd1:
 args    = ["cat", "-n", NULL]
 element = [cat, -n, <, in.txt]
 all	 = all env
 next    = cmd2

cmd2:
 args    = ["grep", "hello", NULL]
 element = [grep, hello, >, out.txt]
  all	 = all env
 next    = NULL
*/