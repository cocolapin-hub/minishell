
#include "../../minishell.h"

// int	create_heredoc(const char *limiter)		// avec fichier tmp
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (-1);
// }

static int	close_and_free(char *line, int fd1, int fd2, int ret)
{
	if (line)
		free(line);
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	return (ret);
}

// stocker le heredoc dans un pipe plutot que dans un fichier tmp : mieux
int	create_heredoc(char *limiter)
{
	int		pipefd[2];		// tab à deux cases car fd[0] et fd[1]
	char	*line;

	if (pipe(pipefd) == -1) // crée un tuyau unidirectionnel pipefd[0] = lecture / pipefd[1] = écriture
		return (-1);
	setup_heredoc_signals();// Ctrl-C annule heredoc, Ctrl-\ ignoré
	while (1)
	{
		g_in_heredoc = 0;
		line = readline("> ");
		if (g_in_heredoc == SIGINT) // CTRL-C
			return (close_and_free(line, pipefd[0], pipefd[1], -2));
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);		// ferme le coté écriture
	setup_sig();			// rétablir signaux du parent
	return (pipefd[0]);
}



// flag pour la fonction open(O_WRONLY | O_CREAT | O_TRUNC, 0644)
// WRONLY = ouvre le fichier en écriture seule
// CREAT  = crée le fichier s'il n'existe pas
// TRUNC  = si le fichier existe, on efface tout avant d'écrire (>)
// APPEND = écrit a la fin sans écraser (>>)

// 0644   = mode Unix (permissions du fichier quand on le crée) droits par défaut -rw-r--r--
			// En octal (0 au début = octal) :
			// 	6 = lecture + écriture (rw-)
			// 	4 = lecture (r--)
			// 	4 = lecture (r--)
			// Donc 0644 = propriétaire :	lecture + écriture
			// 								groupe : lecture seule
			//								autres : lecture seule


/*

lors d'un CTRL-C : bash arrete la saisie, heredoc canceled, la commande avant le heredoc n'est pas lancée et $? vaut 130

On doit traiter le heredoc comme un mini-shell temporaire :

	Quand tu rentres dans create_heredoc, tu changes les signaux :
		SIGINT → tue le heredoc et stoppe l’exécution.
		SIGQUIT → ignoré (comme dans Bash).

	Si l’utilisateur fait Ctrl+C pendant le heredoc :
		tu fermes le pipefd,
		tu libères la mémoire,
		tu retournes une erreur spéciale pour dire au parent : "heredoc annulé".

	Le shell parent doit alors :
		ne pas exécuter la commande,
		mettre last_status = 130.

*/