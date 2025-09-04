/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/04 12:01:35 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char 		*clean_line(char *line)
{
	char 	*new_line;
	char	quote;
	int 	x;
	int 	y;
	int		len;

	len = strlen(line);
	new_line = malloc(sizeof(char) * len + 1);
	if (!new_line)
		return NULL;

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

char		*check_input(char *line)
{
	int x = 0;

	/*ligne vide*/
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		exit (1);
	}

	/*caractères spéciaux*/
	while(line[x])
	{
		if (line[x] < 32 && line[x] != 9)
			line = NULL;
		x++;
	}

	/*longueur excessive*/
	if (x >= MAX_LINE_LEN)
		line = NULL;

	/*espaces et tabulations*/
	line = clean_line(line);

	return line;
}
