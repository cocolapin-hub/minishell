#include "../../minishell.h"


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
