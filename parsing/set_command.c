/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:41:18 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/16 12:59:16 by ochkaoul         ###   ########.fr       */
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

	/*the right t_token*/ //--> not working out yet
	while((*list)->value != PIPE && *list)
	{
		node->element = list;
		if ((*list)->next->value == PIPE || !(*list))
			list = NULL? ???????


			
		*list = (*list)->next;
	}


	/*the same env*/
	node->all = all;

	/*pointer to next*/
	node->next = NULL;

	return(node);
}

void	fill_args(t_token **list, char ***args)
{
	int 	token_count;
	char	*arg;
	int		x = 0;

	while ((*list)->value == WORD)
	{
		token_count++;
		(*list) = (*list)->next;
	}

	*args = malloc(sizeof(char *) * (token_count + 1));
	if (!(*args))
		exit (1); 						//--> end code propery later;
	(*args)[token_count] = 0;

	while ((*list)->value == WORD)
	{
		(*args)[x++] = ft_strdup((*list)->value);
		(*list) = (*list)->next;
	}

	while ((*list)->type != PIPE && (*list))
		(*list) = (*list)->next;

	if ((*list)->next && (*list)->type == PIPE)
		list = (*list)->next;
}

void	set_command(t_command **cmd, t_token *list, t_SHELL *all)
{
	t_command	*new;
	t_token		*tmp;
	char 		**args;

	tmp = list;
	while(list)
	{
		fill_args(&tmp, &args); 					//done
		new = ft_lstnew_cmd(args, &list, all);		//adjuste element (fonction)
		if (!*cmd)
			*cmd = new;
		else
			ft_lstadd_back(cmd, new);
	}
}




/*

cmd1:
 args    = ["cat", "-n", NULL]
 element = [cat, -n, <, in.txt]
 all	 = env
 next    = cmd2

cmd2:
 args    = ["grep", "hello", NULL]
 element = [grep, hello, >, out.txt]
  all	 = env
 next    = NULL


*/