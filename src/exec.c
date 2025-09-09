
#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_command *cmd, t_env *env)
{
	if (!cmd || !cmd->cmd)
		return (1);
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (builtin_echo(cmd->args));
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (builtin_cd(cmd->args, env));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (builtin_export(cmd->args, env));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (builtin_unset(cmd->args, env));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (builtin_env(env));
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (builtin_exit(cmd->args));
	return (1);
}
static void	print_error(char *cmd, char *msg)
{
	//write(2, "minishell: ", 11); zsh ??
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

static void child_process(t_command *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	envp = env_to_tab(env);					// convertit liste chainée en char **
	path = find_in_path(cmd->cmd, envp);
	if (!path)
	{
		print_error(cmd->cmd, "command not found");
		free_split(envp);
		exit(127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		print_error(cmd->cmd, "execution failed");
		free_split(envp);
		exit(1);
	}
}

void	run_command(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd->cmd))
	{
		exec_builtin(cmd, env); 	// pas besoin de fork
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		print_error(cmd->cmd, "fork failed");
		return ;
	}
	if (pid == 0)
		child_process(cmd, env);	// processus enfant
	else
		waitpid(pid, &status, 0);	// parent attend fin de l'enfant
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