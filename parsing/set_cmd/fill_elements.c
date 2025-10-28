#include "../../minishell.h"


void		fill_elements(t_token **list, t_token **elements)
{
	t_token	*start = NULL;
	t_token	*tmp = *list;
	t_token	*end = NULL;
	t_token	*new = NULL;

	tmp = *list;
	if (!(*list) || !list)
	{
		*elements = NULL;
		return ;
	}

	/*fill element struct*/
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			create_cmd(&tmp, &new, &start, &end);
		tmp = tmp->next;
	}
	*elements = start;

	/*move after the pipe for next cmd*/
	if (tmp && tmp->type == PIPE)
		*list = tmp->next;
	else
		*list = tmp;
}
