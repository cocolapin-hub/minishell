/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/16 15:19:09 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_command	*parsing(char *line, t_SHELL *all)
{
	t_token 	*list = NULL;
	t_command 	*cmd = NULL;

	/*Etapes de mon parsing*/
	check_input(line);									// Analyse de l'input
	tokenisation(line, &list, &all);					// Cree les Token  + expansion
	error_handling(&all, &list);						// Analyse syntaxique
	set_command(&cmd, list, all);						// Construction de la structure


	/* ____PRINT CHECK____*/
	// while(list)
	// {
	// 	printf("type: %d\ncmd: %s\n\n", list->type,  list->value);
	// 	list = list->next;
	// }

	/*_____PRINT CMD_____*/
	t_command *cmd_ptr = cmd;

	while (cmd_ptr)
	{
		if (cmd_ptr->args)
		{
			for (int i = 0; cmd_ptr->args[i]; i++)
				printf("arg[%d] = \"%s\"\n", i, cmd_ptr->args[i]);
		}
		else
			printf("args = NULL\n");

		t_token *tok = cmd_ptr->elements;
		if (!tok)
			printf("elements = NULL\n");
		while (tok)
		{
			if (!tok->value)
				printf("!! NULL value at tok %p !!\n", (void*)tok);
			else
				printf("[%s:%d] ", tok->value, tok->type);

			tok = tok->next;
		}
		printf("\n---\n");

		cmd_ptr = cmd_ptr->next;
	}


		return (cmd);
	}



