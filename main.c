/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:14:39 by claffut           #+#    #+#             */
/*   Updated: 2025/09/17 16:14:28 by ochkaoul         ###   ########.fr       */
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

//TO_DO :	// remove leaks
			// remettre les quotes dans token
			// regroup work

// OPTI	:	//merge both ft_lstadd_back_cmd and ft_lstadd_back
			//merge both ft_lstlast_cmd and ft_lstlast

// leaks:	//free cmd dans tokenisation?
			//leaks dans expansion corrige?

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
			end_code(cmd);

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

	free(line);
	end_code(cmd);
    return 0;
}

