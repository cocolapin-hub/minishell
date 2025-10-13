#include "../minishell.h"


// char	*expand_with_quotes(char *line, char *quote, int *x, t_shell **all)
// {
// 	char	*tmp;
// 	int		y;
// 	int		i = 0;;
// 	y = *x + 1;

// 	/*Assign quote*/
// 	*quote = line[y];


// 	while (line[y] && line[y] != *quote)
// 		y++; i++;

// 	if (line[y] == '\0')
// 	{
// 		write(2, "syntax error: unclosed quotes\n", 30);
// 		(*all)->last_status = 258;
// 		return (NULL);
// 	}
// 	else if (line[y] == *quote)
// 		y++;


// 	/*saves the cmd*/
// 	tmp = ft_strdup_m(line, *x + 1, 0);
// 	// if (*quote != 39)
// 	// 	tmp = expansion((*all)->env, (*all)->last_status, tmp, 0);
// 	*x = y + 1;


// 	return (tmp);
// }


char	*outside_quotes(char *line, int *x, int *y, t_shell **all)
{
	char	*tmp;
//	char	quote;

	if (line[*y] == '$' && (line[*y + 1] == 34 || line[*y + 1] == 39))
	{
		(*x)++;
		return(tmp = ft_strdup(""));

		//tmp = expand_with_quotes(line, &quote, y, all);
	}


	else
	{
		while (line[*y] && line[*y] != 34 && line[*y] != 39 && line[*y] != 32
			&& line[*y] != 9 && line[*y] != 60 && line[*y] != 62
			&& line[*y] != 124)
			(*y)++;

		tmp = ft_strdup_m(line, *x, *y - *x);
		tmp = expansion((*all)->env, (*all)->last_status, tmp, 0);
	}


	*x = *y;
	return (tmp);
}