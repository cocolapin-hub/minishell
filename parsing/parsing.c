/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/18 12:06:10 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_command	*parsing(char *line, t_SHELL *all)
{
	t_token 	*list = NULL;
	t_command 	*cmd = NULL;
	char		*cleaned_line;

	(void)cmd;
	(void)all;

	/*ligne vide*/
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		end_code(cmd);
	}

	/*Etapes de mon parsing*/
	cleaned_line = check_input(line);

	if (!cleaned_line)
		return NULL;

	tokenisation(cleaned_line, &list, &all);
	error_handling(&all, &list);

	if(!set_command(&cmd, list, all))
	{
		free(line);
		free_tokens(list);
		end_code(cmd);
	}

	/* ____PRINT CHECK____*/
	// while(list)
	// {
	// 	printf("type: %d\ncmd: %s\n\n", list->type,  list->value);
	// 	list = list->next;
	// }

	if(list)
		free_tokens(list);
	free(cleaned_line);
	return (cmd);
}
