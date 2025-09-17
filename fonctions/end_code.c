/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:04:27 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/17 15:10:34 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	end_code(t_command *cmd)
{
	t_command	*tmp;

	while(cmd)
	{
		tmp = cmd->next;

		if (cmd->all)
			free_env(cmd->all);

		if (cmd->args)
			free_args(cmd->args);

		if (cmd->elements)
			free_tokens(cmd->elements);

		free(cmd);
		cmd = tmp;
	}

	exit(1);
}







//	in case if error before end of parsing:
	// 	free(all);
	// ->	free(list) & free (list->value);
	// ->

//	at the end of code :
//	free(cmd)
		// free(cmd->args);
		// free(cmd->elements);
		// free(cmd->all);
		// free (cmd);

//free list


// ici creer une fonction pour free specifiquement env et la reutiliser a env setup.