
#include "../../minishell.h"

int	g_in_heredoc = 0;	// a mettre dans le main ?

void	sigint_handler(int sig)	// handler de SIGINT (CTRL-C)
{
	(void)sig;
	g_in_heredoc = SIGINT;
	write(1, "^C\n", 3);
	rl_replace_line("", 0);		// vide la ligne courante
	rl_on_new_line();			// prépare readline à afficher un nouveau prompt
	rl_redisplay();				// réafiiche le prompt
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

void	setup_sig(void)						// installe des signaux pour le parent qui attend (minishell)
{
	signal(SIGINT, sigint_handler);			// SIGINT  (ctrl-c)
	signal(SIGQUIT, SIG_IGN);				// ignore sigquit
}

void sigint_heredoc(int sig)
{
    (void)sig;
    g_in_heredoc = SIGINT;
    write(1, "\n", 1);
    close(STDIN_FILENO); // force readline à stopper
}

void setup_heredoc_signals(void)
{
    signal(SIGINT, sigint_heredoc); // Ctrl-C annule le heredoc
    signal(SIGQUIT, SIG_IGN);       // Ctrl-\ ignoré
}


// on n’affiche pas ^\Quit dans le parent. Ça doit seulement se faire quand un enfant est tué par SIGQUIT.

// à appeler au lancement de minishell dans main avant la boucle principale
// signal(SIGQUIT, sigquit_handler);		// SIGQUIT (ctrl-\) 