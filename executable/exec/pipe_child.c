
#include "../../minishell.h"

static void	setup_pipe_fds(int prev_fd, int *pipefd, int has_next)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (has_next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static int	handle_empty_cmd(t_command *cmd, int prev_fd, int *pipefd)
{
	int	redir_status;

	if ((!cmd->args || !cmd->args[0] || !*cmd->args[0]) && cmd->elem)
	{
		setup_pipe_fds(prev_fd, pipefd, cmd->next != NULL);
		redir_status = apply_redir(cmd->elem, cmd->all);
		if (redir_status == -2)
			exit(130);
		if (redir_status != 0)
			fatal_exit("redirection", 1);
		error_code("", "command not found", 127);
		exit(127);
	}
	return (0);
}

void	pipe_child(t_command *cmd, int prev_fd, int *pipefd)
{
	int	r;

	if (handle_empty_cmd(cmd, prev_fd, pipefd))
		return ;
	setup_pipe_fds(prev_fd, pipefd, cmd->next != NULL);
	if (cmd->elem)
	{
		r = apply_redir(cmd->elem, cmd->all);
		if (r == -2)
			exit(130);
		if (r != 0)
			exit(1);
	}
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, cmd->all));
	else
		child_process(cmd, cmd->all->env);
}
