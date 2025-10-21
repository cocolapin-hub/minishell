
//TO DO:	V	//gerer ctr C for exec pipe
				//expansion dans heredoc


				//couper les fonctions dans le parsing
				// -> tokenisation est sous folder dans tokenisation
					// -> tokenisation est lui meme un folder



			//plusieurs fonction de plus de 25 lines
			//frees
			//norminette




// cat >> me""uoi -> pas d'expansion pour le end of file mais il faut retirer les guillemets
// le cat fait l'expansion si il n'y avait pas de ghuillemets dans le end of file


#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_command  *cmd_list = NULL;
    t_shell    all;
    char       *line;

    (void)argc;
    (void)argv;

    // Initialize shell environment
    setup_shell(&all, envp);
    all.last_status = 0;
	all.sig_type = 0;
    // Install signal handlers
    setup_sig();

    while (1)
    {
        // Read input
        line = readline("minishell$ ");
		handles_ctrl_d(line, all, cmd_list);

		if (handles_ctrl_c(all, line) || line[0] == '\0')
		{
			free(line);
			continue ;
		}

        add_history(line);
		parsing(line, &all, &cmd_list);
        free(line); 					// now we can free it safely

        if (!cmd_list)
            continue;

        // Execute commands
        if (cmd_list->next) 			//cmd avec pipe
            exec_pipe(cmd_list, &all);
        else
            run_command(cmd_list);		//cmd sans pipe

        // Free command list
        free_command(cmd_list);
        cmd_list = NULL;
    }

    return (0);
}


// int main(int argc, char **argv, char **envp)
// {
//     t_shell 	all;
//     t_command 	*cmd_list = NULL;
//     char 		*line;

//     (void)argc;
//     (void)argv;

// 	setup_shell(&all, envp);

//     all.last_status = 0;
//     setup_sig();

//     while (1)
//     {
//         line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			// if (g_in_heredoc == SIGINT)
// 			// {
// 			// 	g_in_heredoc = 0;
// 			// 	continue ;
// 			// }
// 			printf("exit\n");
// 			exit_clean_af(&all, cmd_list, all.last_status);
// 		}
// 		if (line[0] != '\0')
// 			add_history(line);
// 		else
// 		{
// 			free(line);
// 			continue ;
// 		}

//         cmd_list = parsing(line, &all);
//        //free(line);						// <-------------handle free later

//         if (!cmd_list)
//             continue ;

//         // Exécution

//         if (cmd_list->next) // il y a un pipe
//             exec_pipe(cmd_list, &all);
//         else
//             run_command(cmd_list);

//         //free_command(cmd_list);			// <--------------handle free later
//         cmd_list = NULL;
//     }


//  //   clear_history();
//  //   free_env(all.env);
//     return (0);
// }
