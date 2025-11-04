/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:45:03 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_redir_in(t_token *redir)
{
	int	fd;

	if (!redir->value || redir->value[0] == 0)
	{
		redir_error(redir->value, "ambiguous redirect");
		return (1);
	}
	fd = open(redir->value, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			redir_error(redir->value, "No such file or directory");
		else if (errno == EACCES)
			redir_error(redir->value, "Permission denied");
		else
			perror("minishell");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_out(t_token *redir)
{
	int	fd;

	if (!redir->value || redir->value[0] == 0)
	{
		redir_error(redir->value, "ambiguous redirect");
		return (1);
	}
	fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (errno == EACCES)
			redir_error(redir->value, "Permission denied");
		else
			perror("minishell");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_append(t_token *redir)
{
	int	fd;

	if (!redir->value || redir->value[0] == '\0')
	{
		redir_error(redir->value, "ambiguous redirect");
		return (1);
	}
	fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		if (errno == EACCES)
			redir_error(redir->value, "Permission denied");
		else
			perror("minishell");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_heredoc(t_token *redir, t_shell *all)
{
	int	fd;

	if (!redir->value || redir->value[0] == '\0')
		return (redir_error(redir->value, "ambiguous redirect"));
	fd = create_heredoc(redir->value, all);
	if (fd == -2)
	{
		all->last_status = 130;
		return (-2);
	}
	if (fd < 0)
		return (redir_error("heredoc", "failed"));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (redir_error("heredoc", strerror(errno)));
	}
	close(fd);
	return (0);
}

int	apply_redir(t_token *redir, t_shell *all)
{
	int	ret;

	while (redir)
	{
		if (check_ambiguous_redirect(redir->value))
			return (1);
		if (redir->type == REDIR_IN)
			ret = handle_redir_in(redir);
		else if (redir->type == REDIR_OUT)
			ret = handle_redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			ret = handle_redir_append(redir);
		else
			ret = handle_redir_heredoc(redir, all);
		if (ret == -2)
			return (-2);
		if (ret != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}
