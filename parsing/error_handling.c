
#include "../minishell.h"

t_token 	*check_unknown_char(t_token *list, t_shell **all)
{
	/*if it is && or ||*/
	if ((strcmp(list->value, "||") == 0 || strcmp(list->value, "&&") == 0))
	{
		write(2, "syntax error: unknown character\n", 32);
		(*all)->last_status = 258;
		return NULL;
	}
	return (list);
}

t_token 	*check_pipe(t_token *list, t_shell **all)
{
	//pipe at the end
	if (list->type == PIPE && list->next == NULL)
	{
		write(2, "syntax error near unexpected token 'newline'\n", 45);
		(*all)->last_status = 258;
		return NULL;
	}

	//pipe followed by pipe or redir
	if (list->type == PIPE && (list->next->type != WORD || list->next->type != 0))
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		(*all)->last_status = 258;
		return NULL;
	}

	return (list);
}

t_token 	*check_redir(t_token *list, t_shell **all)
{
	const char	*token[] = {"|", "<", ">", ">>", "<<"};

	//redirection without file
	if ((list->type == REDIR_IN || list->type == REDIR_OUT || list->type == REDIR_APPEND || list->type == REDIR_HEREDOC) && (list->next == NULL))
	{
		write(2, "syntax error near unexpected token 'newline'\n", 45);
		(*all)->last_status = 258;
		return NULL;
	}

	//redir followed by a redir
	if ((list->type != PIPE && list->type != WORD)
	&& (list->next != NULL && list->next->type != WORD && list->next->type != PIPE))
	{
		write(2, "syntax error near unexpected token '", 36);
		write(2, token[list->type - 1], ft_strlen(token[list->type - 1]));
		write(2, "'\n", 2);
		(*all)->last_status = 258;
		return NULL;
	}

	//redir followed by pipe
	if ((list->type != PIPE && list->type != WORD) && (list->next->type == PIPE))
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		(*all)->last_status = 258;
		return NULL;
	}

	// ; & after redir
	if ((list->type != PIPE && list->type != WORD) && (list->next->type == WORD))
	{
		if ((strcmp(list->next->value, ";") == 0 || strcmp(list->next->value, "&") == 0))
		{
			write(2, "syntax error near unexpected token '", 36);
			write(2, list->next->value, 1);
			write(2, "'\n", 2);
			(*all)->last_status = 258;
			return NULL;
		}
	}

	return (list);
}

void 	error_handling(t_shell **all, t_token **list)
{
	t_token *lst2 	= *list;

	/*checks the first one*/
	if (lst2 && lst2->type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		(*all)->last_status = 258;
		free_tokens(*list);
		return ;
	}

	/*check other syntax*/
	while (lst2)
	{
		if (lst2->type == WORD)
			lst2 = check_unknown_char(lst2, all);

		else if (lst2->type == PIPE)
			lst2 = check_pipe(lst2, all);

		else if (lst2->type != WORD && lst2->type != PIPE)
			lst2 = check_redir(lst2, all);

		/*end if an error was caught*/
		if (!lst2)
		{
			free_tokens(*list);
			return;
		}
		lst2 = lst2->next;
	}

	//*list = lst2;
}

//also add case scenarios for () ; &