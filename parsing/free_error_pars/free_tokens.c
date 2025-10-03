#include "../minishell.h"

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	while(list)
	{
		tmp = list->next;
		free(list->value);
		free (list);
		list = tmp;
	}
}