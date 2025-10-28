
#include "../../minishell.h"

void		fill_args(t_token *list, char ***args)
{
	int		skip_next;
	int		x;

	/*creates args */
	create_args(list, 0, 0, args);

	/*allocate value*/
    skip_next = 0;
    x = 0;
	while (*args && list && list->type != PIPE)
    {
        if (list->type == REDIR_IN || list->type == REDIR_OUT
            || list->type == REDIR_APPEND || list->type == REDIR_HEREDOC)
            skip_next = 1;
        else if (list->type == WORD)
        {
			if (skip_next == 1 && ft_strcmp(list->value, "-n"))
				skip_next = 0;
            else
                (*args)[x++] = ft_strdup(list->value);
				//protection needed here
        }
        list = list->next;
    }
}
