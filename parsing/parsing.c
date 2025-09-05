/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/05 17:23:25 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_command	*parsing(char *line, t_local *env)
{
	t_token 	*list = NULL;
	t_command 	*cmd = NULL;
	(void)env;
	/*Etapes de mon parsing*/

	check_input(line);						// Analyse de l'input
	tokenisation(line, &list);				// Cree les Token
	expansion(env, &list);					// Expansion et quote


	// error_handling();			// Analyse syntaxique
	// set_command();				// Construction de la structure

	/* _______PRINT CHECK_______*/
	while(list)
	{
		printf("type: %d\nquotes: %d\ncmd: %s\n\n", list->type, list->amount, list->value);
		list = list->next;
	}

	return (cmd);
}



