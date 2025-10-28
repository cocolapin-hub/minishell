
#include "../../minishell.h"

static int	check_first_element(t_token *lst2, t_token **list, t_shell **all)
{
	//redirection without file
	if (lst2 && lst2->type == PIPE)
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		(*all)->last_status = 2;
		free_tokens(*list);
		*list = NULL;
		return 0;
	}
	return (1);
}

static t_token *check_syntax_loop(t_token *lst, t_shell **all, t_token **list)
{
	while (lst)
	{
		if (lst->type == WORD)
			lst = check_char(lst, all);
		else if (lst->type == PIPE)
			lst = check_pipe(lst, all);
		else
			lst = check_redir(lst, all);

		if (!lst)
		{
			free_tokens(*list);
			*list = NULL;
			return (NULL);
		}
		lst = lst->next;
	}
	return (lst);
}

void error_handling(t_shell **all, t_token **list)
{
	t_token *lst = *list;

	if (check_first_element(lst, list, all) == 0)
		return;

	check_syntax_loop(lst, all, list);
}

