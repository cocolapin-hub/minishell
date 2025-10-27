
#include "../../minishell.h"


// static void	run_child(t_command *cmd)
// {
// 	//printf("run child\n");
// 	signal(SIGINT, SIG_DFL);								 // mettre les signaux par défaut,
// 	signal(SIGQUIT, SIG_DFL);								 // pour que CTRL-C ou -\ tuent la commande enfant et pas minishell + le parent capture le retour avec waitpid $? est mis à jour (130 ou 131)
// 	child_process(cmd, cmd->all->env);						 // création processus enfant
// }

// int	run_builtin_command(t_command *cmd)		// builtin executé dans le process parent !! donc faut restaurer les FDs après
// {
// 	int	saved_stdin;
// 	int	saved_stdout;
// 	int	status;

// 	saved_stdin = dup(STDIN_FILENO);
// 	saved_stdout = dup(STDOUT_FILENO);
// 	if (saved_stdin == -1 || saved_stdout == -1)
// 		return (print_error(cmd->args[0], "dup failed"), 1);

// 	if (apply_redir(cmd->elem, cmd->all) == 0)
// 		status = exec_builtin(cmd, cmd->all);
// 	else
// 		status = 1;
// 	dup2(saved_stdin, STDIN_FILENO);
// 	dup2(saved_stdout, STDOUT_FILENO);
// 	close(saved_stdin);
// 	close(saved_stdout);
// 	return (status);
// }

// void	run_command(t_command *cmd)
// {
// 	pid_t	pid;
// 	int		ret;

// 	if (is_builtin(cmd->args[0]))
// 	{
// 		ret = apply_redir(cmd->elem, cmd->all);
// 		if (ret == -2)
// 			return ; // interrompu par Ctrl-C
// 		if (ret != 0)
// 			return ; // autre erreur de redirection
// 		cmd->all->last_status = run_builtin_command(cmd);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 		return (print_error(cmd->args[0], "fork failed"), (void)0);
// 	if (pid == 0)
// 		run_child(cmd);
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		signal(SIGQUIT, SIG_IGN);
// 		run_parent(cmd, pid);
// 		setup_sig();
// 	}
// }

// static int	is_dir(const char *path)
// {
// 	struct stat	st;

// 	if (stat(path, &st) == -1)
// 		return (0);
// 	return (S_ISDIR(st.st_mode));
// }

// void	child_process(t_command *cmd, t_local *env)
// {
// 	char	*path;
// 	char	**envp;
// 	struct stat st;

// 	if (apply_redir(cmd->elem, cmd->all) != 0)
// 		exit(1);

// 	envp = env_to_tab(env);
// 	if (!envp)
// 		fatal_error("malloc", 1);

// 	if (ft_strchr(cmd->args[0], '/'))
// 		path = ft_strdup(cmd->args[0]);
// 	else
// 		path = find_in_path(cmd->args[0], env);

// 	if (!path)
// 	{
// 		print_error_exec(cmd->args[0], "command not found");
// 		exit(127);
// 	}
// 	if (stat(path, &st) == -1)
// 	{
// 		print_error_exec(cmd->args[0], strerror(errno));
// 		free(path);
// 		exit(127);
// 	}
// 	if (is_dir(path))
// 	{
// 		print_error_exec(cmd->args[0], "is a directory");
// 		free(path);
// 		exit(126);
// 	}
// 	if (access(path, X_OK) != 0)
// 	{
// 		print_error_exec(cmd->args[0], strerror(errno));
// 		free(path);
// 		exit(126);
// 	}

// 	execve(path, cmd->args, envp);
// 	print_error_exec(cmd->args[0], strerror(errno));
// 	free(path);
// 	exit(126);
// }

// void child_process(t_command *cmd, t_local *env)
// {
// 	char	*path;
// 	char	**envp;
// 	int		redir_status;

// 	redir_status = apply_redir(cmd->elem, cmd->all);
// 	if (redir_status == -2)
// 	{
// 		g_in_heredoc = SIGINT;
// 		exit(130); 												// simplest solution with right pid to parent
// 	}
// 	if (redir_status != 0)										// appliquer les redirs avant execve
// 		fatal_error("redirection", 1);							// erreur ouverture fichier, on exit
// 	envp = env_to_tab(env);										// convertit liste chainée en char **
// 	if (!envp)
// 		fatal_error("malloc", 1);
// // 	if (ft_strchr(cmd->args[0], '/'))
// //         path = ft_strdup(cmd->args[0]);
// //     else
// //         path = find_in_path(cmd->args[0], env);
// //     if (!path || access(path, X_OK) != 0)
// //     {
// //         if (!path)
// //             ft_putstr_fd("minishell: ", 2);
// //         ft_putstr_fd(cmd->args[0], 2);
// //         ft_putstr_fd(": command not found\n", 2);
// //         free(path);
// //         exit(127);
// //     }
// //     if (is_directory(path))
// //     {
// //         ft_putstr_fd("minishell: ", 2);
// //         ft_putstr_fd(cmd->args[0], 2);
// //         ft_putstr_fd(": is a directory\n", 2);
// //         free(path);
// //         exit(126);
// //     }
// //     execve(path, cmd->args, env_to_tab(env));
// // }
// 	//=== Gerer un input qui est juste un path ===//			// a deplacer dans une fonction a part (ligne 85 a 98)
// 	if (ft_strchr(cmd->args[0], '/'))
// 	{
// 		path = ft_strdup(cmd->args[0]);
// 		if (access(path, F_OK) != 0)
// 		{
// 			free(path);
// 			exit(exec_error(cmd->args[0], "No such file or directory", 127));
// 		}
// 		else if (access(path, X_OK) != 0)
// 		{
// 			free(path);
// 			exit(exec_error(cmd->args[0], "Permission denied", 126));
// 		}
// 	}
// 	//============================================//

// 	else
// 		path = find_in_path(cmd->args[0], env);

// 	if (!path)
// 	{
// 		if (!get_env_value(env, "PATH"))
// 			exit(exec_error(cmd->args[0], "No such file or directory", 127));
// 		else
// 			exit(exec_error(cmd->args[0], "command not found", 127));
// 		//free_split(envp);		free ici ??
// 	}
// 	if (execve(path, cmd->args, envp) == -1)
// 	{
// 		free_split(envp);
// 		free(path);
// 		exit(exec_error(cmd->args[0], strerror(errno), 126));	// verif le code d'erreur de bash car je suis pas sur
// 	}
// }

void	child_process(t_command *cmd, t_local *env)
{
	char	*path;
	char	**envp;
	int		redir_status;
	struct	stat st;

	/*redirections */
	redir_status = apply_redir(cmd->elem, cmd->all);
	if (redir_status == -2)
		exit(130);
	if (redir_status != 0)
		fatal_error("redirection", 1);
	envp = env_to_tab(env);
	if (!envp)
		fatal_error("malloc", 1);
	/*chemin */
	if (ft_strchr(cmd->args[0], '/'))
		path = ft_strdup(cmd->args[0]);
	else
		path = find_in_path(cmd->args[0], env);

	if (!path)
	{
		if (!get_env_value(env, "PATH"))
			exit(exec_error(cmd->args[0], "No such file or directory", 127));
		exit(exec_error(cmd->args[0], "command not found", 127));
	}
	/* fichier inexistant ou non exécutable */
	if (stat(path, &st) == -1)
	{
		free_split(envp);
		free(path);
		exit(exec_error(cmd->args[0], "No such file or directory", 127));
	}
	if (S_ISDIR(st.st_mode))
	{
		free_split(envp);
		free(path);
		exit(exec_error(cmd->args[0], "Is a directory", 126));
	}
	if (access(path, X_OK) != 0)
	{
		free_split(envp);
		free(path);
		exit(exec_error(cmd->args[0], "Permission denied", 126));
	}
	/* Exécution */
	execve(path, cmd->args, envp);
	free_split(envp);
	free(path);
	exit(exec_error(cmd->args[0], strerror(errno), 126));
}

static void run_parent(t_command *cmd, pid_t pid)
{
    int	status;
	int	sig;

    waitpid(pid, &status, 0);					// waiting for child to finish
	setup_sig();
    if (WIFEXITED(status))
        cmd->all->last_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        sig = WTERMSIG(status);
        cmd->all->last_status = 128 + sig;
        if (sig == SIGINT)
            write(STDOUT_FILENO, "\n", 1);
        else if (sig == SIGQUIT)
            write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
    }
    else
        cmd->all->last_status = 1;
}

static void	restore_std(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	run_builtin_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;
	int	redir_status;


	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (print_error("dup", strerror(errno)), 1);

	redir_status = apply_redir(cmd->elem, cmd->all);
	if (redir_status == -2)
		ret = 130;
	else if (redir_status != 0)
		ret = 1;
	else
		ret = exec_builtin(cmd, cmd->all);
	restore_std(saved_stdin, saved_stdout);
	return (ret);
}

void	run_command(t_command *cmd)
{
	pid_t	pid;
	char	*path_env;

	path_env = get_env_value(cmd->all->env, "PATH");
	if (cmd->args[0][0] == '\0')	// commande vide ""
	{
		if (!path_env || path_env[0] == '\0')
		{
			ft_putendl_fd("minishell: : No such file or directory", 2);
			cmd->all->last_status = 127;
		}
		else
		{
			ft_putendl_fd("minishell: : command not found", 2);
			cmd->all->last_status = 127;
		}
		return ;
	}
	if (ft_strcmp(cmd->args[0], "..") == 0)
	{
		if (!path_env || path_env[0] == '\0') // PATH unset ou vide
		{
			ft_putendl_fd("minishell: ..: Is a directory", 2);
			cmd->all->last_status = 126;
		}
		else
		{
			ft_putendl_fd("minishell: ..: command not found", 2);
			cmd->all->last_status = 127;
		}
		return ;
	}
	if (ft_strcmp(cmd->args[0], ".") == 0)		// commande '.'
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		cmd->all->last_status = 2;
		return ;
	}
	if (is_builtin(cmd->args[0]))
	{
		cmd->all->last_status = run_builtin_command(cmd);
		return ;
	}
	pid = fork();
	if (pid == -1)
		 return (print_error_exec(cmd->args[0], "fork failed"), (void)0);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		child_process(cmd, cmd->all->env);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		run_parent(cmd, pid);
		setup_sig();	// restaure le handler readline
	}
}


/*
Points techniques importants

	Pourquoi fork ?
		Chaque commande externe s’exécute dans un processus enfant.
		Le parent attend (waitpid) pour ne pas continuer avant la fin de la commande.

	Pourquoi pas de fork pour les builtins ?
		Les builtins doivent modifier l’environnement du processus shell lui-même.
		Si on les exécutait dans un enfant, les changements (cd, export) seraient perdus à la fin du fork.

	env_to_tab
		Transforme t_env * en char ** pour execve.
		Nécessaire car execve ne connaît que les tableaux de chaînes, pas les listes chaînées.

	exit(127) et exit(1)
		Codes standards pour indiquer à l’OS si la commande a échoué ou non.

*/