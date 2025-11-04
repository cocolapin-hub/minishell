/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:44:58 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_heredocs_before_exec(t_command *cmd)
{
	t_token	*redir;
	int		fd;

	redir = cmd->elem;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			fd = create_heredoc(redir->value);
			if (fd < 0)
				return (fd);
			redir->heredoc_fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}

int	handle_heredoc_and_errors(t_pipe *p, t_shell *all)
{
	int	ret;

	ret = process_heredocs_before_exec(p->cmd_list);
	if (ret == -2)
	{
		all->last_status = 130;
		if (p->prev_fd != -1)
			close(p->prev_fd);
		return (-1);
	}
	else if (ret != 0)
	{
		all->last_status = 1;
		if (p->prev_fd != -1)
			close(p->prev_fd);
		return (-1);
	}
	return (0);
}

static void	heredoc_child(int write_fd, char *limiter)
{
	char	*line;

	setup_heredoc_signals();
	close(write_fd - 1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(write_fd);
	_exit(0);
}

static int	heredoc_parent(pid_t pid, int read_fd, int write_fd)
{
	int	status;

	close(write_fd);
	waitpid(pid, &status, 0);
	setup_sig();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(read_fd);
		return (-2);
	}
	return (read_fd);
}

int	create_heredoc(char *limiter)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
		heredoc_child(pipefd[1], limiter);
	return (heredoc_parent(pid, pipefd[0], pipefd[1]));
}
