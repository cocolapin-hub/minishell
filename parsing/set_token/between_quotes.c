
#include "../../minishell.h"


static void	expand_word(char **tmp, char *quote, t_shell **all, t_token **list)
{
	t_token *last = NULL;

	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}

	if (*quote != 39 && (!last || last->type != REDIR_HEREDOC))
		*tmp = expansion((*all)->env, (*all)->last_status, *tmp, quote);
}

char		*between_quotes(char *line, int *x, t_shell **all, t_token **list)
{
	char	quote;
	char	*tmp;
	int		y;

	y = *x + 1;
	quote = line[*x];
	if (line[y] == quote)
	{
		*x += 2;
		return(tmp = ft_strdup(""));
	}

	while (line[y] && line[y] != quote) //in case i am too tight
		y++;

	if (line[y] == '\0')
	{
		write(2, "syntax error: unclosed quotes\n", 30); //<-- there is a function from coco i can use
		(*all)->last_status = 258;
		return (NULL);
	}

	tmp = ft_strdup_m(line, *x + 1, y - *x - 1);
	expand_word(&tmp, &quote, all, list);
	*x = y + 1;
	return (tmp);
}

