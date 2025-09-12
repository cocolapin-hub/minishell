#include "../minishell.h"

int			skip_space_and_tabs(char *line, int x)
{
	while (line[x] == 32 || line[x] == 9)
		x++;

	return(x);
}

int			handles_normal_command(char *line, int x, t_token **list)
{
	t_token	*new;
	char	*cmd;
	int		len;
	int		y;

	len = 0;
	y = x;
	if (line[x] != 34 && line[x] != 39)
	{
		while (line[y] && line[y] != 34 && line[y] != 39 && line[y] != 32 && line[y] != 9
			&& line[y] != 60 && line[y] != 62 && line[y] != 124)
		{
			y++;
			len++;
		}

		/*saves the cmd*/
		cmd = ft_strdup_m(line, x, len);

		/*creats the 1st list element*/
		new = ft_lstnew_token(cmd, ' ');
		if (!*list)
			*list = new;

		/*creats others list element*/
		else
			ft_lstadd_back(list, new);
	}
	return (y);
}

int			handles_quoted_command(char *line, int x, t_token **list)
{
	t_token	*new;
	char	quote;
	char	*cmd;
	int		len;
	int		y;

	len = 0;
	y = x;
	if (line[x] == 34 || line[x] == 39)
	{
		/* creer un element et le remplir */
		quote = line[y];
		y++;
		while (line[y] && line[y] != quote)
		{
			y++;
			len++;
		}
		if (line[y] == '\0')
			quote = 35;

		else if (line[y] == quote)
			y++;

		/*saves the cmd*/
		cmd = ft_strdup_m(line, x + 1, len);

		/*creats the 1st list element*/
		new = ft_lstnew_token(cmd, quote);
		if (!*list)
			*list = new;

		/*creats others list element*/
		else
			ft_lstadd_back(list, new);
	}

	return (y);
}

int			handles_special_char(char *line, int x, t_token **list)
{
	t_token	*new;
	char	*cmd;
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
	new = ft_lstnew_token(cmd, ' ');
	if (!*list)
		*list = new;

	/*creats others list element*/
	else
		ft_lstadd_back(list, new);

	return (y + 1);
}

void		tokenisation(char *line, t_token **list)
// cat -n < in.txt | grep "hello   hello" > out.txt
{
	int 	x = 0;

	while(line[x])
	{
		x = skip_space_and_tabs(line, x);

		if (!line[x])
			break;

		if (line[x] == 39 || line [x] == 34)
			x = handles_quoted_command(line, x, list);

		else if (line[x] == '|' || line[x] == '<' || line[x] == '>')
			x= handles_special_char(line, x, list);

		else
			x = handles_normal_command(line, x, list);
	}
	free(line);
	//return (list);
}
