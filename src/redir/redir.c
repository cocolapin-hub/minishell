
#include "../../minishell.h"

static int	handle_redir_in(t_token *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)			// "< file"
	{
		fd = open(redir->value, O_RDONLY);
		if (fd < 0)
		{
			perror("minishell: redir in");
			return (1);
		}
		dup2(fd, STDIN_FILENO);				// stdin = fd standard input
		close(fd);
		return (0);
	}
}

static int	handle_redir_out(t_token *redir)
{
	int fd;

	if (redir->type == REDIR_OUT)		// "> file"
	{
		fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("minishell: redir out");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);			// stdout = fd standard output
		close(fd);
		return (0);
	}
}

static int	handle_redir_append(t_token *redir)
{
	int fd;

	if (redir->type == REDIR_APPEND)	// ">> file"
	{
		fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("minishell: redir append");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);			// stdout = fd standard output
		close(fd);
		return (0);
	}
}

static int	handle_redir_heredoc(t_token *redir)
{
	int fd;

	if (redir->type == REDIR_HEREDOC)	// "<< limiter"
	{
		fd = create_heredoc(redir->value);
		if (fd < 0)
		{
			perror("heredoc");
			return (1);
		}
		dup2(fd, STDIN_FILENO);				// branche l'entrée standard sur le pipe
		close(fd);
		return (0);
	}
}
int apply_redir(t_token *redir)
{
    while (redir)
    {
		if (redir->type == REDIR_IN && handle_redir_in(redir))
			return (1);
		if (redir->type == REDIR_OUT && handle_redir_out(redir))
			return (1);
		if (redir->type == REDIR_APPEND && handle_redir_append(redir))
			return (1);
		if (redir->type == REDIR_HEREDOC && handle_redir_heredoc(redir))
			return (1);
		redir = redir->next;
    }
    return (0);
}


/*
	dup2
	- duplique "oldfd" dans "newfd" apres les deux FD pointent vers le meme fichier/pipe
	- si "newfd" etait déjà ouvert, il est fermé d'abord puis remplacé par une copie de "oldfd"

Exemple avec un pipe : "ls | grep txt"
		
			Tu crées un pipe :
				int fd[2];
				pipe(fd);   // fd[0] = lecture, fd[1] = écriture

			Dans le premier enfant (ls) :
				dup2(fd[1], 1);   // stdout -> pipe écriture
				close(fd[0]);     // inutile
				close(fd[1]);     // fd original plus utile après dup2
				execve("ls", ...);

			Dans le deuxième enfant (grep) :
				dup2(fd[0], 0);   // stdin -> pipe lecture
				close(fd[0]);
				close(fd[1]);
				execve("grep", ...);

			Résultat :
				ls écrit dans fd[1] (le pipe).
				grep lit depuis fd[0].
				Le noyau fait la liaison entre les deux.



___ SCHEMA PIPE + REDIR  "commande1 < in.txt | commande2 > out.txt"

[Parent minishell]
   |
   +--fork--> [Enfant 1: commande1]
   |             stdin <- in.txt
   |             stdout -> pipe[1]
   |
   +--fork--> [Enfant 2: commande2]
   |             stdin <- pipe[0]
   |             stdout -> out.txt
   |
   +--wait--> attend les deux enfants




Redir	= manipuler dup2 pour associer stdin/stdout à un fichier/pipe.
Pipe	= pipe(fd) + dup2 pour relier stdout du premier et stdin du second.
Ordre	= redirections dans chaque commande → puis pipes → puis execve.

<, >, >> sont simples, elles font :  open() + dup2().
<< (heredoc) est spécial.
	il n'agit pas sur un fichier mais sur une entrée que l'user tape en direct.
	il faut créer un "fichier tmp" ou un "pipe" pour stocker le contenu de l'entrée
	et ensuite on rediriges stdin vers ce contenu


*/