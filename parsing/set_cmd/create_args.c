#include "../../minishell.h"

//proteger les malloc et autre et ajouter les free

void		create_args(t_token *list, int token_count, int skip_next, char ***args)
{
	t_token	*tmp;

	tmp = list;

	/*count len with a tmp == all words but the one right after a redir*/
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			skip_next = 1;

		else if (tmp->type == WORD)
		{
			if (skip_next)
				skip_next = 0;
			else
				token_count++;
		}
		tmp = tmp->next;
	}

	*args = ft_calloc(token_count + 1, sizeof(char *));
	if (!(*args))
		*args = NULL;
	else
		(*args)[token_count] = 0;
}
