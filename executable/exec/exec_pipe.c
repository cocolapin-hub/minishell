/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:44:37 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	pipe_parent(t_pipe *p, t_command *cmd)
{
	p->last_pid = p->pid;
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if (cmd->next)
	{
		close(p->pipefd[1]);
		p->prev_fd = p->pipefd[0];
	}
}

static int	fork_and_execute(t_pipe *p, t_command *cmd)
{
	if (cmd->next && pipe(p->pipefd) == -1)
		return (fatal_exit("pipe", 1), -1);
	p->pid = fork();
	if (p->pid == -1)
		return (error_code("fork", strerror(errno), 1));
	if (p->pid == 0)
	{
		restore_default_signals();
		pipe_child(cmd, p->prev_fd, p->pipefd);
	}
	return (0);
}

static void	update_status(t_shell *all, int status, pid_t wpid, pid_t last_pid)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			all->sig_type = SIGINT;
		else if (sig == SIGQUIT)
			all->sig_type = SIGQUIT;
	}
	if (wpid == last_pid)
	{
		if (WIFEXITED(status))
			all->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			all->last_status = 128 + WTERMSIG(status);
		else
			all->last_status = 1;
	}
}

static void	wait_pipeline(t_shell *all, pid_t last_pid)
{
	int		status;
	pid_t	wpid;

	all->sig_type = 0;
	wpid = wait(&status);
	while (wpid > 0)
	{
		update_status(all, status, wpid, last_pid);
		wpid = wait(&status);
	}
}

void	exec_pipe(t_command *cmd_list, t_shell *all)
{
	t_pipe	p;

	p.prev_fd = -1;
	p.last_pid = -1;
	p.cmd_list = cmd_list;
	ignore_signals();
	while (p.cmd_list)
	{
		if (fork_and_execute(&p, p.cmd_list) == -1)
			return ;
		pipe_parent(&p, p.cmd_list);
		p.cmd_list = p.cmd_list->next;
	}
	wait_pipeline(all, p.last_pid);
	print_signal_message(all);
	setup_sig();
}
