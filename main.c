/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:14:39 by claffut           #+#    #+#             */
/*   Updated: 2025/10/02 16:25:07 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Priorite: // regroup work
//TO_DO :	// remove leaks
			// change le parsing cote cmd --> verifier que ca marche
			// handle quote the new way, discuss it with coco
			// regroup work

// OPTI	:	//merge both ft_lstadd_back_cmd and ft_lstadd_back
			//merge both ft_lstlast_cmd and ft_lstlast

// leaks:	//free cmd dans tokenisation?
			//leaks dans expansion corrige?


void	free_all(t_SHELL *all)
{
    t_local *tmp;

    if (!all)
        return;

    // Libérer chaque maillon de la liste env
    while (all->env)
    {
        tmp = all->env->next;
        if (all->env->key)
            free(all->env->key);
        if (all->env->value)
            free(all->env->value);
        free(all->env);
        all->env = tmp;
    }

    // Libérer la structure shell elle-même
    free(all);
}

int 	main(int argc, char **argv, char **envp)
{
	t_command 	*old_cmd = NULL;
	t_command	*cmd = NULL;
	t_SHELL		*all = NULL;
	char 		*line;

	(void)line;
	(void)argc;
	(void)argv;
	(void)cmd;

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
			old_cmd = cmd;
			cmd = parsing(line, all);
			if(old_cmd)
				end_code(old_cmd);
		}

		free(line);

		/*executable*/
		// if (strlen(line) != 0 && line != NULL)
		// 	exec(cmd);



		//printf("You typed: %s\n", line);

    }

	free_all(all);
//	end_code(cmd);
    return 0;
}



			//add_history(line); --> how to use this ?