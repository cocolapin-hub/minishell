/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 16:40:52 by claffut          ###   ########.fr       */
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
			fd = create_heredoc(redir->value, cmd);
			if (fd < 0)
				return (-2);
			redir->heredoc_fd = fd;
		}
		redir = redir->next;
	}
	return 0;
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

static void	heredoc_child(int write_fd, char *limiter, t_command *cmd)
{
	char	*line;
	char	*expd;

	close(write_fd - 1);
	signal(SIGINT, sigint_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
			break ;
		if (cmd->elem->amount == Q_NONE)
		{
			expd = expansion(cmd->all->env, cmd->all->last_status, &line, NULL);
			if (expd)
				line = expd;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	if (line)
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
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(read_fd);
		return (-2);
	}
	return (read_fd);
}

int	create_heredoc(char *limiter, t_command *cmd)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		setup_sig();
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc);
		heredoc_child(pipefd[1], limiter, cmd);
	}
	return (heredoc_parent(pid, pipefd[0], pipefd[1]));
}
