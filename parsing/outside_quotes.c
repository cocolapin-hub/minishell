#include "../minishell.h"


char	*outside_quotes(char *line, int *x, int *y, t_shell **all)
{
	char	*tmp;
//	char	*pid;

	if (line[*y] == '$' && (line[*y + 1] == 34 || line[*y + 1] == 39))
	{
		(*x)++;
		return(tmp = ft_strdup(""));
	}

	// if (line[*y] == '$' && line[*y + 1] == '$')
	// {
	// 	(*x) += 2;
	// 	(*y) += 2;
	// 	pid = ft_itoa(getpid());
	// 	tmp = ft_strdup(pid);
	// 	return (free(pid), tmp);
	// }

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
