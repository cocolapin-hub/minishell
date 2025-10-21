
#include "../minishell.h"

char	*between_quotes(char *line, char *quote, int *x, t_shell **all, t_token **list)
{
	t_token *last = NULL;
	char	*tmp;
	int		y;


	y = *x + 1;

	/*Assign quote*/
	*quote = line[*x];

	if (line[y] == *quote)
	{
		*x += 2;
		return(tmp = ft_strdup(""));
	}

	while (line[y] && line[y] != *quote)
		y++;

	if (line[y] == '\0')
	{
		write(2, "syntax error: unclosed quotes\n", 30);
		(*all)->last_status = 258;
		return (NULL);
	}

	/*saves the cmd*/  // < -- ISSUE
	tmp = ft_strdup_m(line, *x + 1, y - *x - 1);

	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}

	if (*quote != 39 && (!last || last->type != REDIR_HEREDOC))
		tmp = expansion((*all)->env, (*all)->last_status, tmp, quote);

	*x = y + 1;
	return (tmp);
}