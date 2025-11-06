/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 21:38:26 by claffut          ###   ########.fr       */
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

static int	handle_redir_heredoc(t_token *redir)
{
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
	{
		close(redir->heredoc_fd);
		return (redir_error("heredoc", strerror(errno)));
	}
	close(redir->heredoc_fd);
	return (0);
}

int	apply_redir(t_token *redir)
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
		else if (redir->type == REDIR_HEREDOC)
			ret = handle_redir_heredoc(redir);
		if (ret != 0)
			return (ret);
		redir = redir->next;
	}
	return (0);
}
