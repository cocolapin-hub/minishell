#include "../../minishell.h"

// int	create_heredoc(const char *limiter) // avec fichier tmp
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
// 	if (fd < 0)
// 		return (-1);
// }

int	create_heredoc(char *limiter) // avec pipe,  besy option je pense
{
	int		pipefd[2]; // tab à deux cases car fd[0] et fd[1]
	char	*line;

	if (pipe(pipefd) == -1) // crée un tuyau unidirectionnel pipefd[0] = lecture / pipefd[1] = écriture
		return (-1);
	while (1)
	{
		line = readline("> ");
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
			// Donc 0644 =
			// 	propriétaire : lecture + écriture
			// 	groupe : lecture seule
			// 	autres : lecture seule
