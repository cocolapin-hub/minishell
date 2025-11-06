/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 13:07:41 by claffut          ###   ########.fr       */
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

void	pipe_child(t_command *cmd, int prev_fd, int *pipefd)
{
	int	r;

	setup_pipe_fds(prev_fd, pipefd, cmd->next != NULL);
	if ((!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		&& cmd->elem && cmd->elem->value && cmd->elem->value[0] == '\0')
	{
		error_code("", "command not found", 127);
		_exit(127);
	}
	if (cmd->elem)
	{
		r = apply_redir(cmd->elem);
		if (r == -2)
			_exit(130);
		if (r != 0)
			_exit(1);
	}
	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		error_code("", "command not found", 127);
		_exit(127);
	}
	if (is_builtin(cmd->args[0]))
		_exit(exec_builtin(cmd, cmd->all));
	child_process(cmd, cmd->all->env);
}
