/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:14:39 by claffut           #+#    #+#             */
/*   Updated: 2025/09/11 15:49:21 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// EXEC:
// export VAR=value  						--> add var dans l'env
// unset VAR								--> delete var de l'env
// export 									--> printf stock_local

// NOTE:
// modified ft_strdup
// modified ft_lstnew

//TO_DO :	//start set_command

// BUG	:	//"ec""ho"  fonctionne comme echo mais pas "ec" "ho" ou "ec""ho ".  --> quote handling


int 	main(int argc, char **argv, char **envp)
{
	char 		*line;
	t_command	*cmd = NULL;
	t_SHELL		*all = NULL;

	(void)argc;
	(void)argv;
	setup_signal();
	setup_shell(&all, envp);

    while (1)
    {
		line = readline("minishell$ ");
		if (!line)
			exit (1);

		/*parsing*/
        if (*line)
		{
			cmd = parsing(line, all);
            //add_history(line);
		}

		/*executable*/
		// if (strlen(line) != 0 && line != NULL)
		// 	exec(cmd);


		(void)cmd;
		//printf("You typed: %s\n", line);

    }
    return 0;
}

