/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/11 18:30:12 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_exit(t_shell *all, t_command *cmd_list, int code)
{
	(void)all;
	(void)cmd_list;
	if (all)
		free_env(all);
	if (cmd_list)
		free_command(cmd_list);
	clear_history();
	exit(code);
}

static void	print_heredoc_eof(char *limiter)
{
	write(2, "warning: here-document delimited by end-of-file (wanted `", 57);
	write(2, limiter, ft_strlen(limiter));
	write(2, "`)\n", 3);
}

void	heredoc_exit(int write_fd, char *limiter, char *line, t_command *cmd)
{
	if (!line)
		print_heredoc_eof(limiter);
	if (line)
		free(line);
	close(write_fd);
	free_command(cmd);
	_exit(0);
}
