#include "../../minishell.h"

int	check_ambiguous(char *line, int x, t_token **list, t_shell **all)
{
	t_token	*last;
	char 	*tmp;
	int		y;

	last = NULL;
	tmp = NULL;
	y = x;
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}

	if (last->type == REDIR_IN)
	{
		find_word(&y, x, line, &tmp);
		write(1, tmp, ft_strlen(tmp));
		write(1, ": ambiguous redirect\n", 21);
		(*all)->last_status = 1;
		return (1);
	}
	free(tmp);
	return 0;
}
