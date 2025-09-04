/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/04 16:10:21 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*parsing(char *line)
{
	t_token 	*list = NULL;
	t_command 	*cmd = NULL;

	/*Etapes de mon parsing*/

	check_input(line);				// Analyse de l'input
	tokenisation(line, list);		// Cree les Token


	// quote_handling();			// Expansion et quote
	// error_handling();			// Analyse syntaxique
	// set_command();				// Construction de la structure


	return (cmd);
}
