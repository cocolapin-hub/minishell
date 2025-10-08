
#include "../../minishell.h"

void child_process(t_command *cmd, t_local *env)
{
	char	*path;
	char	**envp;

	if (apply_redir(cmd->elem, cmd->all) != 0)	// appliquer les redirs avant execve
        fatal_error("redirection", 1);	// erreur ouverture fichier, on exit
	envp = env_to_tab(env);				// convertit liste chainée en char **
	if (!envp)
		fatal_error("malloc", 1);
	path = find_in_path(cmd->args[0], env);
	if (!path)
	{
		free_split(envp);
		exit(exec_error(cmd->args[0], "command not found", 127));
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		free_split(envp);
		exit(exec_error(cmd->args[0], strerror(errno), 126));	// verif le code d'erreur de bash car je suis pas sur
	}
}

static void	run_child(t_command *cmd)
{
		signal(SIGINT, SIG_DFL);						 // mettre les signaux par défaut,
		signal(SIGQUIT, SIG_DFL);						 // pour que CTRL-C ou -\ tuent la commande enfant et pas minishell + le parent capture le retour avec waitpid $? est mis à jour (130 ou 131)
		child_process(cmd, cmd->all->env);				 // création processus enfant
}

static void run_parent(t_command *cmd, pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        cmd->all->last_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);
        cmd->all->last_status = 128 + sig;

        // *** MODIFICATION ICI ***
        if (sig == SIGINT)
            write(STDOUT_FILENO, "\n", 1);
        else if (sig == SIGQUIT)
            write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
    }
    else
        cmd->all->last_status = 1;
}

void run_command(t_command *cmd)
{
    pid_t pid;

    if (is_builtin(cmd->args[0]))
    {
        cmd->all->last_status = exec_builtin(cmd, cmd->all);
        return ;
    }

    pid = fork();
    if (pid == -1)
    {
        print_error(cmd->args[0], "fork failed");
        return ;
    }

    if (pid == 0)
        run_child(cmd);
    else
    {
        // *** MODIFICATION ICI ***
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);

        run_parent(cmd, pid);

        // *** MODIFICATION ICI ***
        setup_sig();  // Restaurer les signaux du shell
    }
}


/*
Points techniques importants

	Pourquoi fork ?
		Chaque commande externe s’exécute dans un processus enfant.
		Le parent attend (waitpid) pour ne pas continuer avant la fin de la commande.

	Pourquoi pas de fork pour les builtins ?
		Les builtins doivent modifier l’environnement du processus shell lui-même.
		Si on les exécutait dans un enfant, les changements (cd, export) seraient perdus à la fin du fork.

	env_to_tab
		Transforme t_env * en char ** pour execve.
		Nécessaire car execve ne connaît que les tableaux de chaînes, pas les listes chaînées.

	exit(127) et exit(1)
		Codes standards pour indiquer à l’OS si la commande a échoué ou non.

*/