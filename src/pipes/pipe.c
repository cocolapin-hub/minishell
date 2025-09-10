#include "../../minishell.h"

void	exec_pipe(t_command *cmd_list, t_SHELL *all)
{
	int		pipefd[2];
	int		prev_fd = -1;	// stdin par défaut si pas de pipe avant (valeur sentinelle)
	pid_t	pid;

	while (cmd_list)
	{
		if (cmd_list->next && pipe(pipefd) == -1) // si pas derniere commande, crée un pipe, pipefd[0] = lecture, pipefd[1] = écriture.
		{
			perror("pipe");
			return ;
		}
		pid = fork(); // fork un enfant pour execute la cmd
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)	// ENFANT
		{
			if (prev_fd != -1)	// duplique le fd du pipe précédent en redirigeant son stdin
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd); // on ferme car plus besoin sous ce nom (dup2 a créé un alias)
			}
			if (cmd_list->next)	// si pas la derniere cmd, redirige stdout de l'enfant vers pipefd[1]
			{
				close(pipefd[0]);	// close lecture inutile de l'enfant
				dup2(pipefd[1], STDOUT_FILENO); // dup la sortie vers pipefd[1]
				close(pipefd[1]); // ferme pipefd[1] car dup2 a fait la copie
			}						// IMPORTANT : ces deux dup2 positionnent stdin/out par défaut pour la cmd

			apply_redir(cmd_list->redir);	// applique les redir propre a la cmd, viennent apres la config du pipe (dernier dup2 wins)
			if (is_builtin(cmd_list->args[0]))	// dans un pipe meme le builtin s'execute dans l'enfant, on va gérer plus haut pour les commandes uniques dans exec_command()
				exit(exec_builtin(cmd_list, all->env));	// on exit en appelant exec_builtin pour que l'enfant finisse avec le bon code de sortie
			else
				child_process(cmd_list, all->env);	// fait execve et ne revient pas
		}
		else	// PARENT
		{
			if (prev_fd != -1)
				close(prev_fd);	// ferme ancienne lecture qui n'est plus utile au parent
			if (cmd_list->next) // si on a créé un pipe
			{
				close(pipefd[1]);	// parent ferme extrémité écriture (parent n'écrit pas)
				prev_fd = pipefd[0];	// garde lecture pour la prochaine cmd
			}
		}
		cmd_list = cmd_list->next;
	}
	while (wait(NULL) > 0) // attendre les enfants
		;
}

/*

___ ls -l | grep minishell | wc -l ___

	ls -l  →  écrit dans un pipe  →  grep lit depuis ce pipe  →  écrit dans un autre pipe  →  wc lit depuis ce 2ᵉ pipe.
	Donc : chaîne de tuyaux. Chaque commande est un maillon, et il faut connecter la sortie de l’un à l’entrée du suivant.



*/