#include "../minishell.h"


char		*handles_between_quotes(char *line, char *new_line, int *x, int *y)
{
	char quote;

	quote = 0;
	if (line[*x] == 34 || line[*x] == 39)
	{
		quote = line[*x];
		new_line[(*y)++] = line[(*x)++];
		while (line[*x] && line[*x] != quote)
			new_line[(*y)++] = line[(*x)++];
		if (line[*x] == quote)
			new_line[(*y)++] = line[(*x)++];
	}
	//free(line);
	return new_line;
}

char		*clean_line(char *line, int x, int y)
{
	char 	*new_line;
	int		len;

	len = ft_strlen(line);
	new_line = malloc(sizeof(char) * len + 1);
	if (!new_line)
		return (NULL);

	while(line[x])
	{
		/*handles double spacing/tabs  between quotes*/
		if (line[x] == 34 || line[x] == 39)
			new_line = handles_between_quotes(line, new_line, &x, &y);

		/*handles double spacing and tab*/
		else if ((x != 0 && line[x] == 32 && line[x - 1] == 32)
			|| (x != 0 && line[x] == 9 && line[x - 1] == 9))
			x++;

		/*normal copy*/
		else
			new_line[y++] = line[x++];
	}
	new_line[y] = '\0';
	return (new_line);
}

char		*check_input(char *line, t_shell **all)
{
	char 	c;
	int 	x;

	x = 0;
	// /*caractères spéciaux*/ 								//<-- 2nd function
	while(line[x])
		x++;

	/*longueur excessive*/
	if (x >= MAX_LINE_LEN)
		return (NULL);

	/*line complete d'espace et de !*/
	x = 0;
	if (line[0] == ' ')
	{
		c = line[0];
		while (line[x])
		{
			if (line[x] != c)
				break;
			x++;
		}
		if (line[x] == '\0')
		{
			(*all)->last_status = 0;
			return (NULL);
		}
	}

	/*espaces et tabulations*/
	return (clean_line(line, 0, 0));
}
