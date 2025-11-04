
#include "minishell.h"

static void	exec(t_command  **cmd_list, t_shell *all)
{
 	if ((*cmd_list)->next)
	{
        exec_pipe(*cmd_list, all);
	}
    else
	{
        run_command(*cmd_list);
	}
	free_command(*cmd_list);
	*cmd_list = NULL;
}

int main(int argc, char **argv, char **envp)
{
    t_command  *cmd_list;
    char       *line;
    t_shell    all;

    (void)argc;
    (void)argv;
	all.env = env_init(envp, &all);
	cmd_list = NULL;
	setup_sig();
    while (1)
    {
        line = readline("minishell$ ");
		handles_ctrl_d(line, all, cmd_list);
		if (handles_ctrl_c(all, line) || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		parsing(line, &all, &cmd_list);
        if (!cmd_list)
            continue;
		exec(&cmd_list, &all);
	}
	clean_exit(&all, cmd_list, all.last_status);
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


// int	main(int argc, char **argv, char **envp)
// {
// 	t_command	*cmd_list;
// 	char		*line;
// 	t_shell		all;

// 	(void)argc;
// 	(void)argv;
// 	all.env = env_init(envp, &all);
// 	cmd_list = NULL;
// 	setup_sig();
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		handles_ctrl_d(line, all, cmd_list);
// 		if (handles_ctrl_c(all, line) || line[0] == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		parsing(line, &all, &cmd_list);
// 		if (!cmd_list)
// 			continue;
// 		exec(&cmd_list, &all);
// 	}
// 	clean_exit(&all, cmd_list, all.last_status);
// 	return (0);
// }


int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	t_shell		all;
	char		*line;
	char		**split_cmds;
	int			i;

	cmd_list = NULL;
	all.env = env_init(envp, &all);
	all.last_status = 0;
	all.sig_type = 0;
	setup_sig();

	// === MODE TESTER : ./minishell -c "commandes" === //
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2])
	{
		split_cmds = ft_split(argv[2], ';');
		if (!split_cmds)
			return (fatal_exit("malloc", 1), 1);
		i = 0;
		while (split_cmds[i])
		{
			line = ft_strtrim(split_cmds[i], " \t\n");
			if (!line || !*line)
			{
				free(line);
				i++;
				continue ;
			}
			parsing(line, &all, &cmd_list);
			free(line);
			if (!cmd_list)
			{
				i++;
				continue ;
			}
			if (cmd_list->next)
				exec_pipe(cmd_list, &all);
			else
				run_command(cmd_list);
			free_command(cmd_list);
			cmd_list = NULL;
			i++;
		}
		free_split(split_cmds);
		return (all.last_status);
	}

	// === MODE INTERACTIF NORMAL === //
	while (1)
	{
		line = readline("minishell$ ");
		handles_ctrl_d(line, all, cmd_list);

		if (handles_ctrl_c(all, line) || line[0] == '\0')
		{
			free(line);
			continue ;
		}

		add_history(line);
		parsing(line, &all, &cmd_list);
		free(line);

		if (!cmd_list)
			continue;

		if (cmd_list->next)
			exec_pipe(cmd_list, &all);
		else
			run_command(cmd_list);

		free_command(cmd_list);
		cmd_list = NULL;
	}
	return (all.last_status);
}
