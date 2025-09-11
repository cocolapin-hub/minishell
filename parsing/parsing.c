/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/11 14:41:11 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_command	*parsing(char *line, t_SHELL *all)
{
	t_token 	*list = NULL;
	t_command 	*cmd = NULL;
	(void)all;

	/*Etapes de mon parsing*/
	check_input(line);									// Analyse de l'input
	tokenisation(line, &list);							// Cree les Token
	expansion(all->env, all->last_status, &list);		// Expansion et quote
	error_handling(&all, &list);						// Analyse syntaxique

//	set_command(&cmd, &list);							// Construction de la structure


	/* ____PRINT CHECK____*/
	while(list)
	{
		printf("type: %d\nquotes: %d\ncmd: %s\n\n", list->type, list->amount, list->value);
		list = list->next;
	}

	return (cmd);
}



