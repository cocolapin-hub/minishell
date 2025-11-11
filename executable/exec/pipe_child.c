/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/11 19:38:31 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	exit_pipe_child(t_command *cmd, int status)
{
	t_command	*head;

	head = cmd->all->cmd_head;
	free_env(cmd->all);
	free_command(head);
	_exit(status);
}

void	pipe_child(t_command *cmd, int prev_fd, int *pipefd)
{
	int	r;

	setup_pipe_fds(prev_fd, pipefd, cmd->next != NULL);
	if ((!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		&& cmd->elem && cmd->elem->value && cmd->elem->value[0] == '\0')
	{
		error_code("", "command not found", 127);
		exit_pipe_child(cmd, 127);
	}
	if (cmd->elem)
	{
		r = apply_redir(cmd->elem);
		if (r == -2)
			exit_pipe_child(cmd, 130);
		if (r != 0)
			exit_pipe_child(cmd, 1);
	}
	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		error_code("", "command not found", 127);
		exit_pipe_child(cmd, 127);
	}
	if (is_builtin(cmd->args[0]))
		exit_pipe_child(cmd, exec_builtin(cmd, cmd->all));
	child_process(cmd, cmd->all->env);
}
