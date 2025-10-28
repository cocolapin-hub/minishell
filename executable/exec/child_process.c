
#include "../../minishell.h"

void	run_parent(t_command *cmd, pid_t pid)
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

void	restore_std(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static char *command_path(char *cmd, t_local *env)
{
    if (ft_strchr(cmd, '/'))
        return (ft_strdup(cmd));
    return (find_in_path(cmd, env));
}

static int validate_path(char *path, char *cmd, char **envp)
{
    struct stat st;

    if (stat(path, &st) == -1)
    {
        free_split(envp);
        free(path);
        exit(error_with_code(cmd, "No such file or directory", 127));
    }
    if (S_ISDIR(st.st_mode))
    {
        free_split(envp);
        free(path);
        exit(error_with_code(cmd, "Is a directory", 126));
    }
    if (access(path, X_OK) != 0)
    {
        free_split(envp);
        free(path);
        exit(error_with_code(cmd, "Permission denied", 126));
    }
    return (0);
}

void child_process(t_command *cmd, t_local *env)
{
    char    *path;
    char    **envp;
    int     redir_status;

    redir_status = apply_redir(cmd->elem, cmd->all);
    if (redir_status == -2)
        exit(130);
    if (redir_status != 0)
        fatal_exit("redirection", 1);
    envp = env_to_tab(env);
    if (!envp)
        fatal_exit("malloc", 1);
    path = command_path(cmd->args[0], env);
    if (!path)
    {
        if (!get_env_value(env, "PATH"))
            exit(error_with_code(cmd->args[0], 
                "No such file or directory", 127));
        exit(error_with_code(cmd->args[0], "command not found", 127));
    }
    validate_path(path, cmd->args[0], envp);
    execve(path, cmd->args, envp);
    free_split(envp);
    free(path);
    exit(error_with_code(cmd->args[0], strerror(errno), 126));
}


// void	child_process(t_command *cmd, t_local *env)		ANCIEN PAS NORME QUI MARCHE
// {
// 	char	*path;
// 	char	**envp;
// 	int		redir_status;
// 	struct	stat st;

// 	/*redirections */
// 	redir_status = apply_redir(cmd->elem, cmd->all);
// 	if (redir_status == -2)
// 		exit(130);
// 	if (redir_status != 0)
// 		fatal_error("redirection", 1);
// 	envp = env_to_tab(env);
// 	if (!envp)
// 		fatal_error("malloc", 1);
// 	/*chemin */
// 	if (ft_strchr(cmd->args[0], '/'))
// 		path = ft_strdup(cmd->args[0]);
// 	else
// 		path = find_in_path(cmd->args[0], env);

// 	if (!path)
// 	{
// 		if (!get_env_value(env, "PATH"))
// 			exit(exec_error(cmd->args[0], "No such file or directory", 127));
// 		exit(exec_error(cmd->args[0], "command not found", 127));
// 	}
// 	/* fichier inexistant ou non exécutable */
// 	if (stat(path, &st) == -1)
// 	{
// 		free_split(envp);
// 		free(path);
// 		exit(exec_error(cmd->args[0], "No such file or directory", 127));
// 	}
// 	if (S_ISDIR(st.st_mode))
// 	{
// 		free_split(envp);
// 		free(path);
// 		exit(exec_error(cmd->args[0], "Is a directory", 126));
// 	}
// 	if (access(path, X_OK) != 0)
// 	{
// 		free_split(envp);
// 		free(path);
// 		exit(exec_error(cmd->args[0], "Permission denied", 126));
// 	}
// 	/* Exécution */
// 	execve(path, cmd->args, envp);
// 	free_split(envp);
// 	free(path);
// 	exit(exec_error(cmd->args[0], strerror(errno), 126));
// }