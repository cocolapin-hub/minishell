/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/11 19:43:59 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	validate_path(char *path, char *cmd_name,
							char **envp, t_command *cmd)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		error_code(cmd_name, "No such file or directory", 127);
		exit_child_with_cleanup(cmd, envp, path, 127);
	}
	if (S_ISDIR(st.st_mode))
	{
		error_code(cmd_name, "Is a directory", 126);
		exit_child_with_cleanup(cmd, envp, path, 126);
	}
	if (access(path, X_OK) != 0)
	{
		error_code(cmd_name, "Permission denied", 126);
		exit_child_with_cleanup(cmd, envp, path, 126);
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
		{
			error_code(cmd->args[0], "No such file or directory", 127);
			exit_child_with_cleanup(cmd, envp, NULL, 127);
		}
		error_code(cmd->args[0], "command not found", 127);
		exit_child_with_cleanup(cmd, envp, NULL, 127);
	}
	validate_path(path, cmd->args[0], envp, cmd);
	execve(path, cmd->args, envp);
	error_code(cmd->args[0], strerror(errno), 126);
	exit_child_with_cleanup(cmd, envp, path, 126);
}
