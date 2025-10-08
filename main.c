// TO DO:	// omar : signaux
			// coco : export

			//gerer end code / ctr D etc..
			//gerer les cas rare


			//plusieurs fonction de plus de 25 lines
			//frees
			//norminette

//TO CHANGE:	//set up signal							--> DONE
				//$ cat > | ls error message
				//tokenisation 25 lines

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_shell    all;
    t_command  *cmd_list = NULL;
    char       *line;

    (void)argc;
    (void)argv;

    // Initialize shell environment
    setup_shell(&all, envp);
    all.last_status = 0;

    // Install signal handlers
    setup_sig();

    while (1)
    {
        // Read input
        line = readline("minishell$ ");

		if (!line)
		{
			// Ctrl-D pressed
			printf("exit\n");
			exit_clean_af(&all, cmd_list, all.last_status);
		}

		// Vérifier si c'était un SIGINT
		if (g_in_heredoc == SIGINT)
		{
			g_in_heredoc = 0;  // Reset le flag
			all.last_status = 130;  // exit status pour SIGINT
			free(line);
			continue;
		}

		// Ignore empty lines
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

        // Add non-empty lines to history
        add_history(line);

        // Parse line into commands
        cmd_list = parsing(line, &all);
        free(line); // now we can free it safely

        if (!cmd_list)
            continue;

        // Execute commands
        if (cmd_list->next) // pipe exists
            exec_pipe(cmd_list, &all);
        else
            run_command(cmd_list);

        // Free command list
        free_command(cmd_list);
        cmd_list = NULL;
    }

    return 0;
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
