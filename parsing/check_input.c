#include "../minishell.h"

char		*clean_line(char *line)
{
	char 	*new_line;
	char	quote = 0;
	int		len;
	int 	x;
	int 	y;


	len = ft_strlen(line);
	new_line = malloc(sizeof(char) * len + 1);
	if (!new_line)
		return (NULL);

	y = 0;
	x = 0;
	while(line[x])
	{
		/*handles double spacing/tabs  between quotes*/
		if (line[x] == 34 || line[x] == 39)
		{
			quote = line[x];
			new_line[y++] = line[x++];
			while (line[x] && line[x] != quote)
				new_line[y++] = line[x++];
			if (line[x] == quote)
				new_line[y++] = line[x++];
		}

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
	char 	*new_line;
	int 	x = 0;

	/*pour point virgule*/
	if (line[0] == 59 || (line[0] == 59 && line[1] == 59))
	{
		if (line[0] == 59 && line[1] == 59)
			new_line = ft_strdup(";;");
		else
			new_line = ft_strdup(";");
		return(new_line);
	}

	/*caractères spéciaux*/
	while(line[x])
	{
		if (line[x] < 32 && line[x] != 9)
			return (NULL);
		x++;
	}

	/*longueur excessive*/
	if (x >= MAX_LINE_LEN)
		return (NULL);

	/*pour :*/
	if (strcmp(line, ":") == 1)
	{
		(*all)->last_status = 0;
		return (NULL);
	}

	/*line complete d'espace et de !*/
	x = 0;
	if (line[0] == ' ')
	{
		char c = line[0];
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
	return (clean_line(line));
}
