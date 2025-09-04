/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:14:39 by claffut           #+#    #+#             */
/*   Updated: 2025/09/04 14:55:57 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NOTE:
// modified ft_strdup
// modified ft_lstnew

//TO_DO : finir analyse et tokenisation aujourd'hui

static void    	CTRL_C_handler(int signo)
{
    (void)signo;
    write(2, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void			setup_signal(void)
{
	struct sigaction sa;

	sa.sa_handler = CTRL_C_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);

	/*ctrl_\*/
	signal(SIGQUIT, SIG_IGN);
}

int 	main(void)
{
	t_command	*cmd = NULL;
    char *line;

	setup_signal();
    while (1)
    {
		line = readline("minishell$ ");
		if (!line)
			exit (1);


		/*parsing*/
        if (*line)
		{
			cmd = parsing(line);
            add_history(line);
		}


		/*executable*/
		// if (strlen(line) != 0 && line != NULL)
		// 	exec(cmd);


		(void)cmd;
		printf("You typed: %s\n", line);
        free(line);
    }
    return 0;
}





