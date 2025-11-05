/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 16:50:46 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	run_builtin_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;
	int	redir_status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		if (saved_stdin != -1)
			close(saved_stdin);
		if (saved_stdout != -1)
			close(saved_stdout);
		return (print_err(NULL, "dup", strerror(errno)), 1);
	}
	redir_status = apply_redir(cmd->elem);
	if (redir_status == -2)
		ret = 130;
	else if (redir_status != 0)
		ret = 1;
	else
		ret = exec_builtin(cmd, cmd->all);
	restore_std(saved_stdin, saved_stdout);
	return (ret);
}

static int	handle_empty_command(t_shell *all, char *path_env)
{
	if (!path_env || path_env[0] == '\0')
		print_err(NULL, NULL, "No such file or directory");
	else
		print_err(NULL, NULL, "command not found");
	all->last_status = 127;
	return (1);
}

static int	handle_dot_commands(char *cmd, t_shell *all, char *path_env)
{
	if (ft_strcmp(cmd, "..") == 0)
	{
		if (!path_env || path_env[0] == '\0')
		{
			print_err("..", NULL, "Is a directory");
			all->last_status = 126;
		}
		else
		{
			print_err("..", NULL, "command not found");
			all->last_status = 127;
		}
		return (1);
	}
	if (ft_strcmp(cmd, ".") == 0)
	{
		write(2, ".: filename argument required\n", 30);
		write(2, ".: usage: . filename [arguments]\n", 33);
		all->last_status = 2;
		return (1);
	}
	return (0);
}

int	validate_command(t_command *cmd, t_shell *all)
{
	char	*path_env;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		all->last_status = 127;
		return (1);
	}
	path_env = get_env_value(all->env, "PATH");
	if (cmd->args[0][0] == '\0')
		return (handle_empty_command(all, path_env));
	if (handle_dot_commands(cmd->args[0], all, path_env))
		return (1);
	return (0);
}

void	run_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (handle_redir_only(cmd))
		return ;
	if (validate_command(cmd, cmd->all))
		return ;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (process_heredocs_before_exec(cmd) == -2)
	{
		cmd->all->last_status = 130;
		restore_std(saved_stdin, saved_stdout);
		return ;
	}
	if (handle_redirections(cmd, saved_stdin, saved_stdout))
		return ;
	if (is_builtin(cmd->args[0]))
	{
		cmd->all->last_status = run_builtin_command(cmd);
		restore_std(saved_stdin, saved_stdout);
		return ;
	}
	exec_child_or_parent(cmd);
	restore_std(saved_stdin, saved_stdout);
}
