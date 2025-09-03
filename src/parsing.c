/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/03 16:50:52 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 1. Analyse de l'input
//    - Récupération de la ligne de commande brute depuis l'utilisateur (readline)
//    - Gestion des cas particuliers :
//         -x ligne vide → ignorer et afficher prompt suivant
//         - EOF (Ctrl-D) → quitter le shell
//         -x caractères spéciaux non valides ou non imprimables
//         -x longueur excessive
//         -x gestion des espaces et tabulations


char 		*clean_line(char *line)
{
	char 	*new_line;
	char	quote;
	int 	x;
	int 	y;
	int		len;

	len = ft_strlen(line);
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
int			check_input(char *line)
//check error output (do we keep line = null to send null?)
{
	int x = 0;

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

	/*ligne vide*/
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		exit (1);
	}
	return 0;
}


void		print_error(char *line, char *msg)
{
	write(2, &line, ft_strlen(line));
	write(2, ':', 1);
	write(2, &msg,  ft_strlen(msg));
	write(2, "\n", 1);
}

t_command	*parsing(char *line)
{

	t_command *cmd = NULL;

	/*Etapes de mon parsing*/

	check_input(line);				// Analyse de l'input
	// tokenisation();				// Cree les Token
	// quote_handling();			// Expansion et quote
	// error_handling();			// Analyse syntaxique
	// set_command();				// Construction de la structure


	return (cmd);
}