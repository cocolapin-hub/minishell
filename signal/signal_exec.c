
#include "../minishell.h"

int	g_in_heredoc = 0;						// a mettre dans le main ?

void sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();  // <- CHANGER rl_done = 1 par rl_redisplay()
    g_in_heredoc = 0; //0 a la place de SIGINT;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	g_in_heredoc = SIGQUIT;
	write(STDOUT_FILENO, "^\\Quit (core dumped)\n", 21); // 22 avec le 2eme backslash

	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sigint_heredoc(int sig)
{
    (void)sig;
    g_in_heredoc = SIGINT;
    write(1, "\n", 1);
    close(STDIN_FILENO); 					// force readline à stopper
}

void setup_heredoc_signals(void)
{
    signal(SIGINT, sigint_heredoc); 		// Ctrl-C annule le heredoc
    signal(SIGQUIT, SIG_IGN);       		// Ctrl-\ ignoré
}

void setup_sig(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;  // PAS de SA_RESTART - important!
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}

// on n’affiche pas ^\Quit dans le parent. Ça doit seulement se faire quand un enfant est tué par SIGQUIT.

// à appeler au lancement de minishell dans main avant la boucle principale
// signal(SIGQUIT, sigquit_handler);		// SIGQUIT (ctrl-\)