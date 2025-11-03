
#include "../../minishell.h"

static int	redir_without_file(t_token *list, t_shell **all)
{
	if ((list->type == REDIR_IN || list->type == REDIR_OUT
			|| list->type == REDIR_APPEND || list->type == REDIR_HEREDOC)
		&& (list->next == NULL))
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		(*all)->last_status = 2;
		return (0);
	}
	return (1);
}

static int	redir_in_with_redir_out(t_token *list, t_shell **all)
{
	if (list->type == REDIR_IN && list->next->type == REDIR_OUT)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		(*all)->last_status = 2;
		return (0);
	}
	return (1);
}

static int	redir_with_wrong_redir(t_token *list, t_shell **all)
{
	const char	*token[] = {"|", "<", ">", ">>", "<<"};

	if ((list->type != PIPE && list->type != WORD)
		&& (list->next != NULL && list->next->type != WORD
			&& list->next->type != PIPE))
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, token[list->next->type - 1],
			ft_strlen(token[list->next->type - 1]));
		write(2, "'\n", 2);
		(*all)->last_status = 2;
		return (0);
	}
	return (1);
}

static int	redir_with_pipe(t_token *list, t_shell **all)
{
	if ((list->type != PIPE && list->type != WORD)
		&& (list->next->type == PIPE))
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		(*all)->last_status = 2;
		return (0);
	}
	return (1);
}

t_token	*check_redir(t_token *list, t_shell **all)
{
	if (redir_without_file(list, all) == 0)
		return (NULL);
	if (redir_in_with_redir_out(list, all) == 0)
		return (NULL);
	if (redir_with_wrong_redir(list, all) == 0)
		return (NULL);
	if (redir_with_pipe(list, all) == 0)
		return (NULL);
	return (list);
}
