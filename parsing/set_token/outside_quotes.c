#include "../../minishell.h"


char	*outside_quotes(char *line, int *x, t_shell **all, t_token **list)
{
	char	*quote = NULL;
	t_token *last = NULL;
	int		start;
	char	*tmp;
	int		y;

	y = *x;

	if (line[y] == '$' && (line[y + 1] == 34 || line[y + 1] == 39))
	{
		(*x)++;
		return(tmp = ft_strdup(""));
	}

	else
	{
		start = y;
		while (line[y] && line[y] != 34 && line[y] != 39 && line[y] != 32
			&& line[y] != 9 && line[y] != 60 && line[y] != 62
			&& line[y] != 124)
			(y)++;

		tmp = ft_strdup_m(line, *x, y - *x);

		if (*list)
		{
			last = *list;
			while (last->next)
				last = last->next;
		}

		if (!last || last->type != REDIR_HEREDOC)
			tmp = expansion((*all)->env, (*all)->last_status, tmp, quote);

	}

	if (line[start] == '$' && ft_strcmp(tmp, "") == 0)
	{
		*x = y;
		free(tmp);
		return (SKIP_TOKEN);
	}

	*x = y;
	return (tmp);
}

//peut potentiellement retirer *last et utiliser lst pas pas en pointer dans certain cas de figure
//ou alors en deplacant le else on peut creer last dedans
