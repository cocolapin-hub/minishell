
#include "../../minishell.h"

static int	handle_redir_in(t_token *redir)	// < redirige le stdin depuis le fichier vers la cmd
{
	int	fd;

	if (!redir->value || redir->value[0] == 0)
	{
		redir_error(redir->value, "ambiguous redirect");
		return (1);
	}
	fd = open(redir->value, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)		// enoent code error 2 (no such file)
			redir_error(redir->value, "No such file or directory");
		else if (errno == EACCES)	// eacces code erreur 13 (pernmission denied)
			redir_error(redir->value, "Permission denied");
		else
			perror("minishell"); 	// fallback générique
		return (1);
	}
	dup2(fd, STDIN_FILENO);			// stdin = fd standard input
	close(fd);
	return (0);
}

static int	handle_redir_out(t_token *redir)	// > envoyer stdout dans un fichier
{
	int	fd;

	if (!redir->value || redir->value[0] == 0)
	{
		redir_error(redir->value, "ambiguous redirect");
		return (1);
	}
	fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (errno == EACCES)
			redir_error(redir->value, "Permission denied");
		else
			perror("minishell");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_append(t_token *redir)	// >> ajoute a la fin d'un fichier au lieu d'effacer le contenu
{
	int	fd;

	if (!redir->value || redir->value[0] == '\0')
	{
		redir_error(redir->value, "ambiguous redirect");
		return (1);
	}
	fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		if (errno == EACCES)
			redir_error(redir->value, "Permission denied");
		else
			perror("minishell");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_heredoc(t_token *redir, t_shell *all)	// << shell lit tout jusqu'au EOF et ecrit directement dans le write-end d'un pipe
{
	int	fd;

	if (!redir->value || redir->value[0] == '\0')
		return (redir_error(redir->value, "ambiguous redirect"));
	fd = create_heredoc(redir->value);	// crée le pipe et return pipefd[0] : lecture
	if (fd == -2)
	{
		all->last_status = 130;  // SIGINT
		return (-2);             // on signale une interruption (ctrlc par exemple)
	}
	if (fd < 0)
		return (redir_error("heredoc", "failed"));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (redir_error("heredoc", strerror(errno)));
	}
	close(fd);
	return (0);
}


int	apply_redir(t_token *redir, t_shell *all)
{
	int	ret;

	// write(1, "ici\n", 4);
	// if (redir->type == REDIR_IN) write(1, "redir.in\n", 9);
	// if (redir->type == REDIR_OUT) write(1, "redir.out\n", 10);
	while (redir)
	{
		if (!redir->value || redir->value[0] == '\0')
			return (redir_error(redir->value, "ambiguous redirect"));
		ret = 0;
		if (redir->type == REDIR_IN)
			ret = handle_redir_in(redir);
		else if (redir->type == REDIR_OUT)
			ret = handle_redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			ret = handle_redir_append(redir);
		else if (redir->type == REDIR_HEREDOC)
			ret = handle_redir_heredoc(redir, all);
		if (ret == -2) 		// heredoc interrompu par ctrl-C
			return (-2);
		if (ret != 0)
			return (1);		// erreur réelle (si ret == 0 alors aucune erreur)
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


Cas d’erreurs possibles

Fichier inexistant (< in.txt)
→ "minishell: in.txt: No such file or directory"

Permission refusée (> out.txt en read-only)
→ "minishell: out.txt: Permission denied"

Ambiguous redirect (expansion qui vide la valeur : > $LOL)
→ "minishell: $LOL: ambiguous redirect"


*/