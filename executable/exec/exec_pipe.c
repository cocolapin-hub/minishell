
#include "../../minishell.h"

static void	pipe_parent(t_pipe *p, t_command *cmd)
{
	p->last_pid = p->pid;		// on met a jour le dernier PID
	if (p->prev_fd != -1)		// on garde le pid du dernier lancé
		close(p->prev_fd);		// ferme ancienne lecture qui n'est plus utile au parent
	if (cmd->next)				// si on a créé un pipe
	{
		close(p->pipefd[1]);		// parent ferme extrémité écriture (parent n'écrit pas)
		p->prev_fd = p->pipefd[0];	// la sortie de ce pipe devient l'entrée de la prochaine cmd
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
static int	fork_and_execute(t_pipe *p, t_command *cmd)
{
	if (cmd->next && pipe(p->pipefd) == -1)
		return (fatal_exit("pipe", 1), -1);
	p->pid = fork();
	if (p->pid == -1)
		return (error_code("fork", strerror(errno), 1));
	if (p->pid == 0)
	{
		restore_default_signals();
		pipe_child(cmd, p->prev_fd, p->pipefd);
	}
	return (0);
}

static void	print_signal_message(t_shell *all)
{
	if (all->sig_type == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (all->sig_type == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void exec_pipe(t_command *cmd_list, t_shell *all)
{
    t_pipe 	p;

    p.prev_fd = -1;
    p.last_pid = -1;
	p.cmd_list = cmd_list;
	ignore_signals();
 	while (p.cmd_list)
    {
		if (fork_and_execute(&p, p.cmd_list) == -1)
			return ;
        pipe_parent(&p, p.cmd_list);
        p.cmd_list = p.cmd_list->next;
    }
    wait_pipeline(all, p.last_pid);
	print_signal_message(all);
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