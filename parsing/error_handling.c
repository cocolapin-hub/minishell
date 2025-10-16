
#include "../minishell.h"

t_token 	*check_char(t_token *list, t_shell **all)
{
	char c;
	char s;


	/*if it is many ; et &*/
	c = list->value[0];
	if (c == ';' || c == '&')
	{
		if (list->value[0] == c && list->value[1] == c)
		{
			write(2, "syntax error near unexpected token `", 36);
			write(2, list->value, 2);
			write(2, "'\n", 2);
			(*all)->last_status = 2;
			return (NULL);
		}
	}

	/*if it is one ; et &*/
	s = ft_strbrk(list->value, ";&{}[]()*?!");
	if (s)
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &s , 1);
		write(2, "'\n", 2);
		(*all)->last_status = 2;
		return (NULL);
	}

	// /*if cat >> then again a redir*/
	// if(list->next->value)

	return (list);
}

t_token 	*check_pipe(t_token *list, t_shell **all)
{
	//pipe at the end
	if (list->type == PIPE && list->next == NULL)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		(*all)->last_status = 2;
		return NULL;
	}

	//pipe followed by pipe or redir
	if (list->type == PIPE && (list->next->type != WORD || list->next->type != 0))
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		(*all)->last_status = 2;
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
		write(2, "syntax error near unexpected token `newline'\n", 45);
		(*all)->last_status = 2;
		return NULL;
	}

	// le cas ou: <>
	if (list->type == REDIR_IN && list->next->type == REDIR_OUT)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		(*all)->last_status = 2;
		return NULL;
	}

	//redir followed by a redir
	if ((list->type != PIPE && list->type != WORD)
	&& (list->next != NULL && list->next->type != WORD && list->next->type != PIPE))
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, token[list->next->type - 1], ft_strlen(token[list->next->type - 1]));
		write(2, "'\n", 2);
		(*all)->last_status = 2;
		return NULL;
	}

	//redir followed by pipe
	if ((list->type != PIPE && list->type != WORD) && (list->next->type == PIPE))
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		(*all)->last_status = 2;
		return NULL;
	}

	// ; & after redir    --> aussi gerer &&
	if ((list->type != PIPE && list->type != WORD) && (list->next->type == WORD))
	{
		if ((strcmp(list->next->value, ";") == 0 || strcmp(list->next->value, "&") == 0))
		{
			write(2, "syntax error near unexpected token `", 36);
			write(2, list->next->value, 1);
			write(2, "'\n", 2);
			(*all)->last_status = 2;
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
		write(2, "syntax error near unexpected token `|'\n", 39);
		(*all)->last_status = 2;
		free_tokens(*list);
		return ;
	}

	/*check the first ;s or &s*/
	else if (lst2 && lst2->type == WORD)
	{
		lst2 = check_char(lst2, all);
		if (!lst2)
		{
			free_tokens(*list);
			*list = NULL;
			return;
		}
	}

	/*check other syntax*/
	while (lst2)
	{
		// if (lst2->type == WORD)
		// 	lst2 = check_unknown_char(lst2, all);

		if (lst2 && lst2->type == WORD)
		{
			lst2 = check_char(lst2, all);
			if (!lst2)
			{
				free_tokens(*list);
				*list = NULL;
				return;
			}
		}
		else if (lst2->type == PIPE)
			lst2 = check_pipe(lst2, all);

		else if (lst2->type != WORD && lst2->type != PIPE)
			lst2 = check_redir(lst2, all);

		/*end if an error was caught*/
		if (!lst2)
		{
			free_tokens(*list);
			*list = NULL;
			return;
		}
		lst2 = lst2->next;
	}

	//*list = lst2;
}
