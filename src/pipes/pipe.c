#include "../../minishell.h"

void	exec_pipe(t_command *cmd_list, t_SHELL *all)
{
	int		pipefd[2];
	int		prev_fd = -1;	// stdin par défaut si pas de pipe avant (valeur sentinelle)
	pid_t	pid;
	pid_t	last_pid = -1;	// on garde le dernier enfant (dernier fork qui est la commande la plus à droite du pipe) on doit l'utiliser pour $?
	int		status;

	while (cmd_list)
	{
		if (cmd_list->next && pipe(pipefd) == -1)	// si next existe, on connecte cette cmd à la suivante: crée un pipe, pipefd[0] = lecture, pipefd[1] = écriture.
		{
			perror("pipe");
			return ;
		}
		pid = fork();	// fork un enfant pour execute la cmd (chaque cmd du pipe s'exec dans un processus(enfant))
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)	// ENFANT
		{
			if (prev_fd != -1)		// si fd du pipe précédent existe
			{
				dup2(prev_fd, STDIN_FILENO);	// dup2 #1 : duplique le fd du pipe précédent sur stdin (fd 0)
				close(prev_fd);		// on ferme car plus besoin sous ce nom (dup2 a créé un alias)
			}
			if (cmd_list->next)		// si pas la derniere cmd, redirige stdout(sortie) de l'enfant vers pipefd[1]
			{
				close(pipefd[0]);	// close lecture inutile de l'enfant
				dup2(pipefd[1], STDOUT_FILENO);		// dup2 #2 : dup la sortie vers pipefd[1]
				close(pipefd[1]);	// ferme pipefd[1] car dup2 a fait la copie
			}							// IMPORTANT  : ces deux dup2 positionnent stdin/out par défaut pour la cmd 
										//			(apply_redir peut ensuite appeler d'autrs dup2 pour écraser ces réglages avec un redir > ou <)
			if (apply_redir(cmd_list->redir) != 0)	// applique les redir propre a la cmd, viennent apres la config du pipe (dernier dup2 wins)
                exit(1);
			if (is_builtin(cmd_list->args[0]))		// dans un pipe meme le builtin s'execute dans l'enfant, on va gérer plus haut pour les commandes uniques dans exec_command()
				exit(exec_builtin(cmd_list));		// on exit en appelant exec_builtin pour que l'enfant finisse avec le bon code de sortie ET leurs modifications d’environnement ne doivent pas affecter le shell parent (c’est le comportement standard)
			else
				child_process(cmd_list, cmd_list->all->env);		// fait execve et ne revient pas
		}
		else		// PARENT
		{
			last_pid = pid;			// on garde le pid du dernier lancé
			if (prev_fd != -1)
				close(prev_fd);		// ferme ancienne lecture qui n'est plus utile au parent
			if (cmd_list->next)		// si on a créé un pipe
			{
				close(pipefd[1]);		// parent ferme extrémité écriture (parent n'écrit pas)
				prev_fd = pipefd[0];	// la sortie de ce pipe devient l'entrée de la prochaine cmd
			}
		}
		cmd_list = cmd_list->next;
	}
	while (wait(&status) > 0)	// attendre tous les enfants + récup statut du dernier
	{
		if (pid == last_pid)	// uniquement le dernier process
		{
			if (WIFEXITED(status))			// WIFEXITED et WEXITSTATUS récup le code de retour si le process s'est terminé normalement
				all->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))	// WIFSIGNALED et WTERMSIG si process tué par un signal (Ctrl-C)
				all->last_status = 128 + WTERMSIG(status);	// on imite bash
			else
				all->last_status = 1;
		}
	}
}
/*

___ ls -l | grep minishell | wc -l ___

	ls -l  →  écrit dans un pipe  →  grep lit depuis ce pipe  →  écrit dans un autre pipe  →  wc lit depuis ce 2ᵉ pipe.
	Donc : chaîne de tuyaux. Chaque commande est un maillon, et il faut connecter la sortie de l’un à l’entrée du suivant.


	résumé des étapes :	1) créer un pipe
						2) prendre la lecture (stdin) de la cmd précédente
						3) rediriger ecriture (stdout) vers pipefd[1]
						4) appliquer les redir (qui vont mofifier les stdin/out du pipe)
						5) exec builtin ou external

Pour chaque commande :

		if cmd->next : pipe(pipefd).
		fork() :
			enfant :
				si prev_fd != -1 -> dup2(prev_fd, 0).
				if cmd->next -> dup2(pipefd[1], 1).
				close les FD inutiles.
				apply_redirections(cmd->redir) (doit gérer << aussi).
				if builtin -> exit(exec_builtin(cmd)) else execve(...).
			parent :
				close(prev_fd) si != -1.
				if cmd->next : close(pipefd[1]); prev_fd = pipefd[0]; else prev_fd = -1.
		ensuite attendre tous les enfants et stocker le dernier statut dans all->last_status 

*/