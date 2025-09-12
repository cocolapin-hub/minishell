/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/12 15:07:22 by ochkaoul         ###   ########.fr       */
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
	tokenisation(line, &list, &all);					// Cree les Token et gere le cas ou les guillemets sont jamais ferme
	//expansion(all->env, all->last_status, &list);		// Expansion et quote

//	error_handling(&all, &list);						// Analyse syntaxique

//	set_command(&cmd, &list);							// Construction de la structure

	/* ____PRINT CHECK____*/
	while(list)
	{
		printf("type: %d\ncmd: %s\n\n", list->type,  list->value);
		list = list->next;
	}

	return (cmd);
}



