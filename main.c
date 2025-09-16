/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:14:39 by claffut           #+#    #+#             */
/*   Updated: 2025/09/16 14:56:26 by ochkaoul         ###   ########.fr       */
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

//TO_DO :	//-
			//-
			//-
			//finish set cmdmake re

// BUG	:	//echo -nnnnnnnn and echo -n   -n    -n works but not -n-n-n --> exec

// OPTI	:	//merge both ft_lstadd_back_cmd and ft_lstadd_back
			//merge both ft_lstlast_cmd and ft_lstlast

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
            //add_history(line); --> how to use this ?
		}

		/*executable*/
		// if (strlen(line) != 0 && line != NULL)
		// 	exec(cmd);


		(void)cmd;
		//printf("You typed: %s\n", line);

    }
    return 0;
}

