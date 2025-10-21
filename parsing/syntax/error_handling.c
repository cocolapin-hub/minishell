
#include "../../minishell.h"


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
		lst2 = check_first_word(lst2, all);
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
