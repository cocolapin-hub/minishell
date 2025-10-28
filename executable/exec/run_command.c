
#include "../../minishell.h"

static int	run_builtin_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;
	int	redir_status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		if (saved_stdin != -1)
			close(saved_stdin);
		if (saved_stdout != -1)
			close(saved_stdout);
		return (print_err(NULL, "dup", strerror(errno)), 1);
	}
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

static int	handle_empty_command(t_shell *all, char *path_env)
{
	if (!path_env || path_env[0] == '\0')
		print_err(NULL, NULL, "No such file or directory");
	else
		print_err(NULL, NULL, "command not found");
	all->last_status = 127;
	return (1);
}

static int	handle_dot_commands(char *cmd, t_shell *all, char *path_env)
{
	if (ft_strcmp(cmd, "..") == 0)
	{
		if (!path_env || path_env[0] == '\0')
		{
			print_err("..", NULL, "Is a directory");
			all->last_status = 126;
		}
		else
		{
			print_err("..", NULL, "command not found");
			all->last_status = 127;
		}
		return (1);
	}
	if (ft_strcmp(cmd, ".") == 0)
	{
		write(2, "minishell: .: filename argument required\n", 41);
		write(2, ".: usage: . filename [arguments]\n", 33);
		all->last_status = 2;
		return (1);
	}
	return (0);
}

int	validate_command(t_command *cmd, t_shell *all)
{
	char	*path_env;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		all->last_status = 127;
		return (1);
	}
	path_env = get_env_value(all->env, "PATH");
	if (cmd->args[0][0] == '\0')
		return (handle_empty_command(all, path_env));
	if (handle_dot_commands(cmd->args[0], all, path_env))
		return (1);
	return (0);
}

void	run_command(t_command *cmd)
{
	pid_t	pid;

	if (validate_command(cmd, cmd->all))
		return ;
	if (is_builtin(cmd->args[0]))
	{
		cmd->all->last_status = run_builtin_command(cmd);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (print_err(cmd->args[0], NULL, "fork failed"), (void)0);
	if (pid == 0)
	{
		restore_default_signals();
		child_process(cmd, cmd->all->env);
	}
	else
	{
		ignore_signals();
		run_parent(cmd, pid);
		setup_sig();
	}
}

// void	run_command(t_command *cmd)			ANCIENNE VERSION QUI MARCHE
// {
// 	pid_t	pid;
// 	char	*path_env;
// 	int 	saved_stdin;
//     int 	saved_stdout;

//     saved_stdin = dup(STDIN_FILENO);
//     saved_stdout = dup(STDOUT_FILENO);
//     if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')	// protege contre null, et le cas ""
//     {
//         if (cmd->elem)	// si y'a un redir
//         {
//             int r = apply_redir(cmd->elem, cmd->all);	// apply redir se charge de print les errors et return 1 si !fichier
// 			dup2(saved_stdin, STDIN_FILENO);
// 			dup2(saved_stdout, STDOUT_FILENO);
// 			close(saved_stdin);
// 			close(saved_stdout);
//             if (r == -2)	// apply_redir return -2 si heredoc interrompu
//                 cmd->all->last_status = 130;
//             else if (r != 0)	// apply_redir already printed the error et si il a return 0 c'est que c'est bon
//                 cmd->all->last_status = 1;
// 			return ;
//         }	// No command and no redirection => nothing to do
        
//         close(saved_stdin);
// 		close(saved_stdout);
//     }
// 	path_env = get_env_value(cmd->all->env, "PATH");
// 	if (cmd->args[0][0] == '\0')	// commande vide ""
// 	{
// 		if (!path_env || path_env[0] == '\0')
// 		{
// 			ft_putendl_fd("minishell: : No such file or directory", 2);
// 			cmd->all->last_status = 127;
// 		}
// 		else
// 		{
// 			ft_putendl_fd("minishell: : command not found", 2);
// 			cmd->all->last_status = 127;
// 		}
// 		return ;
// 	}
// 	if (ft_strcmp(cmd->args[0], "..") == 0)
// 	{
// 		if (!path_env || path_env[0] == '\0') // PATH unset ou vide
// 		{
// 			ft_putendl_fd("minishell: ..: Is a directory", 2);
// 			cmd->all->last_status = 126;
// 		}
// 		else
// 		{
// 			ft_putendl_fd("minishell: ..: command not found", 2);
// 			cmd->all->last_status = 127;
// 		}
// 		return ;
// 	}
// 	if (ft_strcmp(cmd->args[0], ".") == 0)		// commande '.'
// 	{
// 		ft_putstr_fd("minishell: .: filename argument required\n", 2);
// 		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
// 		cmd->all->last_status = 2;
// 		return ;
// 	}
// 	if (is_builtin(cmd->args[0]))
// 	{
// 		cmd->all->last_status = run_builtin_command(cmd);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 		 return (print_error_exec(cmd->args[0], "fork failed"), (void)0);
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGTSTP, SIG_DFL);
// 		child_process(cmd, cmd->all->env);
// 	}
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		signal(SIGQUIT, SIG_IGN);
// 		run_parent(cmd, pid);
// 		setup_sig();	// restaure le handler readline
// 	}
// }




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