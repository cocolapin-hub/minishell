
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
	else if (line[y] == *quote)
		y++;
	/*saves the cmd*/
	tmp = ft_strdup_m(line, *x + 1, y - *x - 2);
	if (*quote != 39)
		tmp = expansion((*all)->env, (*all)->last_status, tmp, 0);
	*x = y;
	return (tmp);
}

char	*outside_quotes(char *line, int *x, int *y, t_shell **all)
{
	char	*tmp;

	while (line[*y] && line[*y] != 34 && line[*y] != 39 && line[*y] != 32
		&& line[*y] != 9 && line[*y] != 60 && line[*y] != 62
		&& line[*y] != 124)
		(*y)++;
	tmp = ft_strdup_m(line, *x, *y - *x);
	tmp = expansion((*all)->env, (*all)->last_status, tmp, 0);
	*x = *y;
	return (tmp);
}

int	handles_command(char *line, int x, t_token **list, t_shell **all)
{
	t_token	*new;
	char	*cmd;
	char	*tmp;
	char	quote;
	int		y;

	cmd = ft_strdup("");
	quote = 0;
	y = x;
	while (line[x])
	{
		/*condition de fin*/
		if (line[x] == 32 || line[x] == 9 || line[x] == 124 || line[x] == 60
			|| line[x] == 62 )
			break ;

		/*attrape entre guillemet*/
		if (line[x] == 39 || line [x] == 34)
		{
			tmp = between_quotes(line, &quote, &x, all);
			y = x;
		}

		/*attrape en dehors des guillemet*/
		else
			tmp = outside_quotes(line, &x, &y, all);

		if (!tmp)
		{
			free(cmd);
			return (-1);
		}
		cmd = ft_strjoin(cmd, tmp);
		free(tmp);
	}

	/*creats the 1st list element*/
	new = ft_lstnew_token(cmd);
	if (!*list)
		*list = new;

	/*creats others list element*/
	else
		ft_lstadd_back(list, new);

	//free(cmd);
	return (x);
}

int		handles_special_char(char *line, int x, t_token **list)
{
	t_token	*new;
	char	*cmd = NULL;
	int		y;

	y = x;

	/*saves the pipe*/
	if (line[x] == 124)
		cmd = ft_strdup_m(line, x, 1);

	/*saves arrows*/
	else if (line[x] == 60 || line[x] == 62)
	{
		if (line[x + 1] == line[x])
		{
			cmd = ft_strdup_m(line, x, 2);
			y++;
		}
		else
			cmd = ft_strdup_m(line, x, 1);
	}

	/*creats the 1st list element*/
	new = ft_lstnew_token(cmd);
	if (!*list)
		*list = new;

	/*creats others list element*/
	else
		ft_lstadd_back(list, new);

	return (y + 1);
}

t_token	*tokenisation(char *line, t_token **list, t_shell **all)
{
	int	x;

	x = 0;
	while (line[x])
	{
		while (line[x] == 32 || line[x] == 9)
			x++;
		if (line[x] == '|' || line[x] == '<' || line[x] == '>')
			x = handles_special_char(line, x, list);
		else
		{
			x = handles_command(line, x, list, all);
			if ((*all)->last_status == 258 || x == -1)
			{
				free_tokens(*list);
				return (NULL);
			}
		}
	}
	return (*list);
}