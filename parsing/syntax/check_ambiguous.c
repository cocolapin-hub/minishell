
#include "../../minishell.h"

int	check_ambiguous(char *line, int x, t_token **list, t_shell **all)
{
	t_token	*last;
	char	*tmp;
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
	find_word(&y, x, line, &tmp);
	if (last->type == REDIR_IN && ft_strcmp(tmp, "") != 0)
	{
		write(1, tmp, ft_strlen(tmp));
		write(1, ": ambiguous redirect\n", 21);
		(*all)->last_status = 1;
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
