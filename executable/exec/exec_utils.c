/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 13:31:47 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	handle_redir_only(t_command *cmd)
// {
// 	int	redir_status;
// 	int	saved_stdin;
// 	int	saved_stdout;

// 	if (!cmd->elem || (cmd->args && cmd->args[0]))
// 		return (0);
// 	saved_stdin = dup(STDIN_FILENO);
// 	saved_stdout = dup(STDOUT_FILENO);
// 	redir_status = apply_redir(cmd->elem);
// 	dup2(saved_stdin, STDIN_FILENO);
// 	dup2(saved_stdout, STDOUT_FILENO);
// 	close(saved_stdin);
// 	close(saved_stdout);
// 	if (redir_status == 0)
// 	{
// 		cmd->all->last_status = 0;
// 		return (1);
// 	}
// 	cmd->all->last_status = 1;
// 	return (1);
// }

int	handle_redir_only(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;
	int	no_cmd;

	no_cmd = (!cmd->args || cmd->args[0] == NULL || cmd->args[0][0] == '\0');
	if (!cmd->elem || !no_cmd)
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	status = process_heredocs_before_exec(cmd);
	if (status == -2)
	{
		restore_std(saved_stdin, saved_stdout);
		cmd->all->last_status = 130;
		return (1);
	}
	status = apply_redir(cmd->elem);
	restore_std(saved_stdin, saved_stdout);
	if (status == 0)
		cmd->all->last_status = 0;
	else
		cmd->all->last_status = 1;
	return (1);
}

int	check_redirections(t_command *cmd)
{
	int	status;

	status = apply_redir(cmd->elem);
	if (status == -2)
		return (cmd->all->last_status = 130, -1);
	if (status != 0)
		return (cmd->all->last_status = 1, -1);
	return (0);
}

int	check_ambiguous_redirect(char *value)
{
	int	i;

	if (!value || !value[0])
		return (redir_error(value, " : No such file or directory"), 1);
	i = 0;
	while (value[i])
	{
		if (value[i] == ' ')
			return (redir_error(value, "ambiguous redirect"), 1);
		i++;
	}
	return (0);
}

int	handle_redirections(t_command *cmd, int saved_stdin, int saved_stdout)
{
	int	redir_status;

	redir_status = apply_redir(cmd->elem);
	if (redir_status != 0)
	{
		restore_std(saved_stdin, saved_stdout);
		if (redir_status == -2)
			cmd->all->last_status = 130;
		else
			cmd->all->last_status = 1;
		return (1);
	}
	return (0);
}

void	exec_child_or_parent(t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_err(cmd->args[0], NULL, "fork failed");
		return ;
	}
	if (pid == 0)
	{
		restore_default_signals();
		child_process(cmd, cmd->all->env);
	}
	else
	{
		ignore_signals();
		run_parent(cmd, pid);
		setup_sig();
	}
}
