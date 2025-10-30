
#include "../minishell.h"

t_command	*ft_lstnew_cmd(char **args, t_token *elements, t_shell *all)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return NULL;
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