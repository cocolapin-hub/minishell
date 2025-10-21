#include "../../minishell.h"


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