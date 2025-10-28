
#include "../../minishell.h"


static int	find_word(int *y, int x, char *line, char **tmp)
{
	int start;

	start = *y;
	while (line[*y] && line[*y] != 34 && line[*y] != 39 && line[*y] != 32
		&& line[*y] != 9 && line[*y] != 60 && line[*y] != 62
		&& line[*y] != 124)
		(*y)++;

	*tmp = ft_strdup_m(line, x, *y - x);
	return (start);
}

static void	expand_word(char **tmp, char quote, t_shell **all, t_token **list)
{
	t_token *last = NULL;

	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}

	if (!last || last->type != REDIR_HEREDOC)
		*tmp = expansion((*all)->env, (*all)->last_status, *tmp, &quote);

}

char		*outside_quotes(char *line, int *x, t_shell **all, t_token **list)
{
	int		start;
	char	*tmp = NULL;
	int		y;

	y = *x;

	if (line[y] == '$' && (line[y + 1] == 34 || line[y + 1] == 39))
	{
		(*x)++;
		return(tmp = ft_strdup(""));
	}
	else
	{
		start = find_word(&y, *x, line, &tmp);
		expand_word(&tmp, 0, all, list);
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
