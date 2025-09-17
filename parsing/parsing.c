/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/17 16:10:12 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_command	*parsing(char *line, t_SHELL *all)
{
	t_token 	*list = NULL;
	t_command 	*cmd = NULL;

	/*ligne vide*/
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		end_code(cmd);
	}

	/*Etapes de mon parsing*/
	line = check_input(line);

	if (!line)
		return NULL;

	tokenisation(line, &list, &all);
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

	return (cmd);



//	note:	//strdup exit a place de close cleanly
			//ft_strjoin exit a place de close cleanly
}
