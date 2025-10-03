
#include "../minishell.h"

void    	CTRL_C_handler(int signo)
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