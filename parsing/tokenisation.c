/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:14:23 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/04 16:09:11 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int		skip_space_and_tabs(char *line, int x)
{
	while (line[x] == 32 || line[x] == 9)
		x++;

	return(x);
}

int		handles_normal_command(char *line, int x, t_token **list)
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
		cmd = ft_strdup(line, x, len);

		/*creats the 1st list element*/
		new = ft_lstnew(cmd, ' ');
		if (!*list)
			*list = new;

		/*creats others list element*/
		else
			ft_lstadd_back(list, new);
	}
	return (y);
}

int		handles_quoted_command(char *line, int x, t_token **list)
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
		if (line[y] == quote)
			y++;

		/*saves the cmd*/
		cmd = ft_strdup(line, x + 1, len);

		/*creats the 1st list element*/
		new = ft_lstnew(cmd, quote);
		if (!*list)
			*list = new;

		/*creats others list element*/
		else
			ft_lstadd_back(list, new);
	}

	return (y);
}

t_token		*tokenisation(char *line, t_token *list)
// cat -n < in.txt | grep "hello   hello" > out.txt
{
	char	*element;
	int 	x = 0;

	while(line[x])
	{
		x = skip_space_and_tabs(line, x);

		if (!line[x])
			break;

		if (line[x] == 39 || line [x] == 34)
			x = handles_quoted_command(line, x, &list);

		else
			x = handles_normal_command(line, x, &list);
	}

	//point back to head if necessary
	return (list);
}
