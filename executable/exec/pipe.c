#include "../../minishell.h"

static void	pipe_child(t_command *cmd, int prev_fd, int *pipefd)
{
	if (prev_fd != -1)		// si fd du pipe précédent existe
	{
		dup2(prev_fd, STDIN_FILENO);		// dup2 #1 : duplique le fd du pipe précédent sur stdin (fd 0)
		close(prev_fd);		// on ferme car plus besoin sous ce nom (dup2 a créé un alias)
	}
	if (cmd->next)			// si pas la derniere cmd, redirige stdout(sortie) de l'enfant vers pipefd[1]
	{
		close(pipefd[0]);	// close lecture inutile de l'enfant
		dup2(pipefd[1], STDOUT_FILENO);		// dup2 #2 : dup la sortie vers pipefd[1]
		close(pipefd[1]);	// ferme pipefd[1] car dup2 a fait la copie
	}						// IMPORTANT  : ces deux dup2 positionnent stdin/out par défaut pour la cmd
							//			(apply_redir peut ensuite appeler d'autrs dup2 pour écraser ces réglages avec un redir > ou <)
	if (apply_redir(cmd->elem, cmd->all) != 0)		// applique les redir propre a la cmd, viennent apres la config du pipe (dernier dup2 wins)
		fatal_error("redir", 1);
	if (is_builtin(cmd->args[0]))			// dans un pipe meme le builtin s'execute dans l'enfant, on va gérer plus haut pour les commandes uniques dans exec_command()
		exit(exec_builtin(cmd));			// on exit en appelant exec_builtin pour que l'enfant finisse avec le bon code de sortie ET leurs modifications d’environnement ne doivent pas affecter le shell parent (c’est le comportement standard)
	else
		child_process(cmd, cmd->all->env);	// fait execve et ne revient pas
}

static void	pipe_parent(t_pipe *mescouilles, t_command *cmd)
{
	mescouilles->last_pid = mescouilles->pid;	// on met a jour le dernier PID
	if (mescouilles->prev_fd != -1)				// on garde le pid du dernier lancé
		close(mescouilles->prev_fd);			// ferme ancienne lecture qui n'est plus utile au parent
	if (cmd->next)								// si on a créé un pipe
	{
		close(mescouilles->pipefd[1]);			// parent ferme extrémité écriture (parent n'écrit pas)
		mescouilles->prev_fd = mescouilles->pipefd[0];	// la sortie de ce pipe devient l'entrée de la prochaine cmd
	}
}

static void wait_pipeline(t_shell *all, pid_t last_pid)
{
    int status;
    pid_t wpid;

    while ((wpid = wait(&status)) > 0)
    {
        if (wpid == last_pid)
        {
            if (WIFEXITED(status))
                all->last_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
            {
                int sig = WTERMSIG(status);
                all->last_status = 128 + sig;

                // *** modification est ici ***
                if (sig == SIGINT)
                    write(STDOUT_FILENO, "\n", 1);
                else if (sig == SIGQUIT)
                    write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
            }
            else
                all->last_status = 1;
        }
    }
}

void exec_pipe(t_command *cmd_list, t_shell *all)    //<-- modified
{
    t_pipe mescouilles;

    mescouilles.prev_fd = -1;
    mescouilles.last_pid = -1;

    // *** modification est ici ***
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    while (cmd_list)
    {
        if (cmd_list->next && pipe(mescouilles.pipefd) == -1)
            fatal_error("pipe", 1);

        mescouilles.pid = fork();
        if (mescouilles.pid == -1)
            exit(exec_error("fork", strerror(errno), 1));

        if (mescouilles.pid == 0)  // ENFANT
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            pipe_child(cmd_list, mescouilles.prev_fd, mescouilles.pipefd);
        }
        else  // PARENT
            pipe_parent(&mescouilles, cmd_list);

        cmd_list = cmd_list->next;
    }

    wait_pipeline(all, mescouilles.last_pid);

    // *** modification est ici ***
    setup_sig();  // Restaurer les signaux du shell
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