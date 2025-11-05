/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/05 20:55:38 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static int	pipe_loop_step(t_pipe *p, t_shell *all)
{
	if (handle_heredoc_and_errors(p, all) == -1)
		return (-1);
	if (fork_and_execute(p, p->cmd_list) == -1)
	{
		all->last_status = 1;
		if (p->prev_fd != -1)
			close(p->prev_fd);
		return (-1);
	}
	p->last_pid = p->pid;
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if (p->cmd_list->next)
	{
		close(p->pipefd[1]);
		p->prev_fd = p->pipefd[0];
	}
	return (0);
}

static void	pipe_loop(t_pipe *p, t_shell *all)
{
	while (p->cmd_list)
	{
		if (pipe_loop_step(p, all) == -1)
			return ;
		p->cmd_list = p->cmd_list->next;
	}
}

static void	exec_wait_pipeline(t_shell *all, pid_t last_pid)
{
	int		status;
	pid_t	wpid;
	int		sigint_seen;

	sigint_seen = 0;
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			sigint_seen = 1;
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				all->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				all->last_status = 128 + WTERMSIG(status);
				all->sig_type = WTERMSIG(status);
			}
			else
				all->last_status = 1;
		}
		wpid = wait(&status);
	}
	if (sigint_seen && all->last_status != 130)
		all->last_status = 130;
}

// void	exec_pipe(t_command *cmd_list, t_shell *all)
// {
// 	t_pipe	p;

// 	p.prev_fd = -1;
// 	p.last_pid = -1;
// 	p.cmd_list = cmd_list;
// 	ignore_signals();
// 	pipe_loop(&p, all);
// 	exec_wait_pipeline(all, p.last_pid);
// 	if (all->sig_type == SIGINT)
// 		write(STDOUT_FILENO, "\n", 1);
// 	print_signal_message(all);
// 	setup_sig();
// }

void exec_pipe(t_command *cmd_list, t_shell *all)
{
    t_pipe p;

    p.prev_fd = -1;
    p.last_pid = -1;
    p.cmd_list = cmd_list;

    // Parent : gérer SIGINT et SIGQUIT pour le shell interactif
    setup_sig();

    pipe_loop(&p, all);

    exec_wait_pipeline(all, p.last_pid);

    if (all->sig_type == SIGINT)
        write(STDOUT_FILENO, "\n", 1);
    else if (all->sig_type == SIGQUIT)
        write(STDOUT_FILENO, "Quit (core dumped)\n", 19);

    // Remettre les handlers classiques pour le shell
    setup_sig();
}
