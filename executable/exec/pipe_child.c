
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

static int	handle_empty_pipe_cmd(t_command *cmd, int prev_fd, int *pipefd)
{
	int	redir_status;

	if ((!cmd->args || !cmd->args[0] || !*cmd->args[0]) && !cmd->elem)
	{
		setup_pipe_fds(prev_fd, pipefd, cmd->next != NULL);
		redir_status = apply_redir(cmd->elem, cmd->all);
		if (redir_status == -2)
			exit(130);
		if (redir_status != 0)
			fatal_exit("redirection", 1);
		error_with_code("", "command not found", 127);
		exit(127);
	}
	return (0);
}

void	pipe_child(t_command *cmd, int prev_fd, int *pipefd)
{
	if (handle_empty_pipe_cmd(cmd, prev_fd, pipefd))
		return ;
	setup_pipe_fds(prev_fd, pipefd, cmd->next != NULL);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, cmd->all));
	else
		child_process(cmd, cmd->all->env);
}

//	ANCIENNE VERSION QUI MARCHE
// static void	pipe_child(t_command *cmd, int prev_fd, int *pipefd)
// {
// 	int redir_status;

// 	// === Check for empty/invalid command FIRST ===
// 	if ((!cmd->args || !cmd->args[0] || !*cmd->args[0]) && !cmd->elem)
// 	{
// 		// Still need to set up pipes properly even if command is invalid
// 		if (prev_fd != -1)
// 		{
// 			dup2(prev_fd, STDIN_FILENO);
// 			close(prev_fd);
// 		}
// 		if (cmd->next)
// 		{
// 			close(pipefd[0]);
// 			dup2(pipefd[1], STDOUT_FILENO);
// 			close(pipefd[1]);
// 		}

// 		// Apply redirections (might have redirections even with empty command)
// 		redir_status = apply_redir(cmd->elem, cmd->all);
// 		if (redir_status == -2)
// 		{
// 			g_in_heredoc = SIGINT;
// 			exit(130);
// 		}
// 		if (redir_status != 0)
// 			fatal_error("redirection", 1);

// 		exec_error("", "command not found", 127); //<-- une histoire de buffer
// 		exit(127);
// 	}

// 	// === Normal command setup ===
// 	if (prev_fd != -1)
// 	{
// 		dup2(prev_fd, STDIN_FILENO);
// 		close(prev_fd);
// 	}

// 	if (cmd->next)
// 	{
// 		close(pipefd[0]);
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		close(pipefd[1]);
// 	}

// 	// Apply redirections
// 	// redir_status = apply_redir(cmd->elem, cmd->all);
// 	// if (redir_status == -2)
// 	// {
// 	// 	write(1, "dane\n", 5);
// 	// 	g_in_heredoc = SIGINT;
// 	// 	exit(130);
// 	// }
// 	// if (redir_status != 0)
// 	// 	fatal_error("redirection", 1);
// 	// Execute builtin or external command
// 	if (is_builtin(cmd->args[0]))
// 		exit(exec_builtin(cmd, cmd->all));
// 	else
// 		child_process(cmd, cmd->all->env);  // This calls exit() internally
// }