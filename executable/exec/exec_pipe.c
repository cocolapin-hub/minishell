
#include "../../minishell.h"

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
    int sig;
    int status;
    pid_t wpid;

    all->sig_type = 0;
    while ((wpid = wait(&status)) > 0)
    {
        if (WIFSIGNALED(status))
        {
            sig = WTERMSIG(status);
            if (sig == SIGINT)
                all->sig_type = SIGINT;
            else if (sig == SIGQUIT)
                all->sig_type = SIGQUIT;
        }
        if (wpid == last_pid)
        {
            if (WIFEXITED(status))
                all->last_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                all->last_status = 128 + WTERMSIG(status);
            else
                all->last_status = 1;
        }
    }
}

void exec_pipe(t_command *cmd_list, t_shell *all)
{
    t_pipe 	mescouilles;

    mescouilles.prev_fd = -1;
    mescouilles.last_pid = -1;
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
	if (all->sig_type == SIGINT)
        write(STDOUT_FILENO, "\n", 1);
    else if (all->sig_type == SIGQUIT)
        write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
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