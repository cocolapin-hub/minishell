#include "../../minishell.h"

void	fill_elements(t_token **list, t_token **elements)
{
	t_token	*start;
	t_token	*tmp;
	t_token	*end;
	t_token	*new;

	start = NULL;
	tmp = *list;
	end = NULL;
	new = NULL;
	if (!(*list) || !list)
	{
		*elements = NULL;
		return ;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			create_cmd(&tmp, &new, &start, &end);
		tmp = tmp->next;
	}
	*elements = start;
	if (tmp && tmp->type == PIPE)
		*list = tmp->next;
	else
		*list = tmp;
}
