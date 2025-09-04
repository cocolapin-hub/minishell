
#include "../minishell.h"
#include "../libft/libft.h"
#include <sys/wait.h>

static void	print_error(char *cmd, char *msg)
{
	//write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

static void child_process(t_command *cmd, char **envp)
{
	char	*path;

	path = find_in_path(cmd->cmd, envp);
	if (!path)
	{
		print_error(cmd->cmd, "command not found");
		exit(127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		print_error(cmd->cmd, "execution failed");
		exit(1);
	}
}

void	exec_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	// if (is_builtin(cmd->cmd))
	// 	exec_builtin(cmd, envp);
	// else
	// 	exec_external(cmd, envp);	fork/execve
	pid = fork();
	if (pid == -1)
		return (print_error(cmd->cmd, "fork failed"));
	if (pid == 0)
		child_process(cmd, envp);
	else
		waitpid(pid, &status, 0);
	
}

/*
Résumé de exec_command

	Parent (minishell) appelle fork().
		s’il échoue : erreur.
		s’il réussit : un nouveau processus enfant est créé.
	Enfant (pid == 0) :
		trouve le chemin avec find_in_path.
		si rien trouvé → afficher "command not found", exit(127).
		sinon, execve(path, args, envp).
		si execve échoue → afficher une erreur, exit(1).
	Parent (pid > 0) :
		waitpid(pid, &status, 0).
		stocker le code de retour → servira pour $?
*/