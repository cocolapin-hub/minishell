
#include "../../minishell.h"

void	run_parent(t_command *cmd, pid_t pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
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

void	restore_std(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static char	*command_path(char *cmd, t_local *env)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_in_path(cmd, env));
}

static int	validate_path(char *path, char *cmd, char **envp)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		free_split(envp);
		free(path);
		exit(error_code(cmd, "No such file or directory", 127));
	}
	if (S_ISDIR(st.st_mode))
	{
		free_split(envp);
		free(path);
		exit(error_code(cmd, "Is a directory", 126));
	}
	if (access(path, X_OK) != 0)
	{
		free_split(envp);
		free(path);
		exit(error_code(cmd, "Permission denied", 126));
	}
	return (0);
}

void	child_process(t_command *cmd, t_local *env)
{
	char	*path;
	char	**envp;

	envp = env_to_tab(env);
	if (!envp)
		fatal_exit("malloc", 1);
	path = command_path(cmd->args[0], env);
	if (!path)
	{
		if (!get_env_value(env, "PATH"))
			exit(error_code(cmd->args[0], "No such file or directory", 127));
		exit(error_code(cmd->args[0], "command not found", 127));
	}
	validate_path(path, cmd->args[0], envp);
	execve(path, cmd->args, envp);
	free_split(envp);
	free(path);
	exit(error_code(cmd->args[0], strerror(errno), 126));
}
