
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

int exec_builtin(t_command *cmd) // *cmd = pointeur sur la variable locale utiliser par la fonction pour acceder a la structure entière
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd->args, cmd->all->env));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd->args, cmd->all->env));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd->args, cmd->all->env));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(cmd->all->env));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit_clean_af(cmd->all, cmd, cmd->all->last_status);
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

void child_process(t_command *cmd, t_local *env)
{
	char	*path;
	char	**envp;

	if (apply_redir(cmd->elem) != 0) // appliquer les redirs avant execve
        fatal_error("redirection", 1); // erreur ouverture fichier, on sort
	envp = env_to_tab(env);					// convertit liste chainée en char **
	path = find_in_path(cmd->args[0], env);
	if (!path)
	{
		print_error(cmd->args[0], "command not found");
		free_split(envp);
		exit(127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		print_error(cmd->args[0], "execution failed");
		free_split(envp);
		exit(1);
	}
}

static void	run_child(t_command *cmd)
{
		signal(SIGINT, SIG_DFL);						 // mettre les signaux par défaut,
		signal(SIGQUIT, SIG_DFL);						 // pour que CTRL-C ou -\ tuent la commande enfant et pas minishell + le parent capture le retour avec waitpid $? est mis à jour (130 ou 131)
		child_process(cmd, cmd->all->env);				 // création processus enfant
}

static void	run_parent(t_command *cmd, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);							// parent attend fin de l'enfant + maj last_status en dessous
	if (WIFEXITED(status))
		cmd->all->last_status = WEXITSTATUS(status);	// succes normal
	else if (WIFSIGNALED(status))
		cmd->all->last_status = 128 + WTERMSIG(status);	// si process tué par un sig : last_status = 128
	else
		cmd->all->last_status = 1;					 	// si signal ou plantage
}

void	run_command(t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd->args[0]))
	{
		cmd->all->last_status = exec_builtin(cmd);		 // pas besoin de fork
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		print_error(cmd->args[0], "fork failed");
		return ;
	}
	if (pid == 0)
		run_child(cmd);
	else
		run_parent(cmd, pid);
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