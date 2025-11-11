/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/11 19:47:50 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec(t_command **cmd_list, t_shell *all)
{
	if ((*cmd_list)->next)
	{
		exec_pipe(*cmd_list, all);
	}
	else
	{
		run_command(*cmd_list);
	}
	free_command(*cmd_list);
	*cmd_list = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	char		*line;
	t_shell		all;

	(void)argc;
	(void)argv;
	all.env = env_init(envp, &all);
	cmd_list = NULL;
	setup_sig();
	while (1)
	{
		line = readline("minishell$ ");
		handles_ctrl_d(line, all, cmd_list);
		parsing(line, &all, &cmd_list);
		if (!cmd_list)
			continue ;
		exec(&cmd_list, &all);
	}
	clean_exit(&all, cmd_list, all.last_status);
	return (0);
}
