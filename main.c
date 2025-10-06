// TO DO:	// omar : env + expansion
			// coco : signaux

			//gerer end code / ctr D etc..
			//gerer les cas rare


			//plusieurs fonction de plus de 25 lines
			//frees
			//norminette



#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_shell 	all;
    t_command 	*cmd_list = NULL;
    char 		*line;

    (void)argc;
    (void)argv;

	setup_shell(&all, envp);

    all.last_status = 0;
    setup_sig();

    while (1)
    {
        line = readline("minishell$ ");
		if (!line)
		{
			if (g_in_heredoc == SIGINT)
			{
				g_in_heredoc = 0;
				continue ;
			}
			printf("exit\n");
			exit_clean_af(&all, cmd_list, all.last_status);
		}
		if (line[0] != '\0')
			add_history(line);


        cmd_list = parsing(line, &all);
       //free(line);						// <-------------handle free later

        if (!cmd_list)
            continue ;

        // Exécution

        if (cmd_list->next) // il y a un pipe
            exec_pipe(cmd_list, &all);
        else
            run_command(cmd_list);

        //free_command(cmd_list);			// <--------------handle free later
        cmd_list = NULL;
    }

 //   clear_history();
 //   free_env(all.env);
    return (0);
}
