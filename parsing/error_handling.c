
#include "../minishell.h"

t_token 	*check_unknown_char(t_token *list, t_shell **all)
{
	/*if it is && or ||*/
	if ((strcmp(list->value, "||") == 0 || strcmp(list->value, "&&") == 0))
	{
		write(2, "syntax error: unkwon character\n", 31);
		(*all)->last_status = 258;
		return NULL;
	}
	return (list);
}

t_token 	*check_pipe_and_redir(t_token *list, t_shell **all)
{
	const char	*token[] = {"|", "<", ">", ">>", "<<"};

	if ((list->type == PIPE && (list->next == NULL || list->next->type != WORD))
	|| ((list->type == REDIR_IN || list->type == REDIR_OUT)
	&& (list->next == NULL || list->next->type != WORD)))
	{
		write(2, "syntax error near unexpected token '", 36);
		write(2, token[list->type - 1], ft_strlen(token[list->type - 1]));
		write(2, "'\n", 2);
		(*all)->last_status = 258;
		return NULL;
	}

	return (list);
}


void 	error_handling(t_shell **all, t_token **list)
{
	t_token *lst2 	= *list;

	/*checks the first one*/
	if (lst2 && lst2->type != WORD)
	{
		write(2, "syntax error :start with pipe or redir\n", 39);
		(*all)->last_status = 258;
		free_tokens(*list);
	}

	/*check other syntax*/
	while (lst2)
	{
		if (lst2->type == WORD)
			lst2 = check_unknown_char(lst2, all);

		else if (lst2->type != WORD)
			lst2 = check_pipe_and_redir(lst2, all);

		/*end if an error was caught*/
		if (!lst2)
		{
			free_tokens(*list);
			return;
		}
		lst2 = lst2->next;
	}
}