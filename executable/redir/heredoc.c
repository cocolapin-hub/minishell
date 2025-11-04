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

static int	close_and_free(char *line, int fd1, int fd2, int ret)
{
	if (line)
		free(line);
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	return (ret);
}

int	create_heredoc(char *limiter, t_shell *all)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (g_in_heredoc == SIGINT)
			return (close_and_free(line, pipefd[0], pipefd[1], -2));
		if (!line || ft_strcmp(line, limiter) == 0)
			break ;
		if (all->cmd_head->elem->amount == Q_NONE)
			line = expansion(all->env, all->last_status, line, 0);
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	setup_sig();
	return (pipefd[0]);
}
