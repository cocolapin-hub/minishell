
#include "../minishell.h"

char	*between_quotes(char *line, char *quote, int *x, t_shell **all)
{
	char	*tmp;
	int		y;


	y = *x + 1;

	/*Assign quote*/
	*quote = line[*x];

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

	if (*quote != 39)
		tmp = expansion((*all)->env, (*all)->last_status, tmp, 0);

	*x = y + 1;
	return (tmp);
}