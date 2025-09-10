
#include "../minishell.h"
#include "../libft/libft.h"

static char	*get_path_line(t_local *env)
{
	while (env)
	{
		if(ft_strcmp(env->key, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*build_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*find_in_path(char *cmd, t_local *env)
{
	char	**dirs;
	char	*path_line;
	char	*full;
	int		i;

	path_line = get_path_line(env);
	if (!path_line)
		return (NULL);
	dirs = ft_split(path_line, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full = build_path(dirs[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (free_split(dirs), full);
		free(full);
		i++;
	}
	free_split(dirs);
	return (NULL);
}

/*

//Ce qu’on doit vraiment faire côté exécution
	Récupérer la commande dans ta structure t_command (ex : cmd = "cat", args = ["cat", "-n", NULL]).
	Trouver son chemin complet (via $PATH).
	Lancer avec execve(full_path, args, envp).
	Attendre le processus avec waitpid.

// avec "" ls -l -a " le parsing aura produit :
	cmd = "ls"
	args = {"ls", "-l", "-a", NULL} // le tableau doit etre termin par NULL et argv[0] = cmd
	find_in_path("ls", envp) doit renvoyer : /bin/ls
		// Pour ça, il faut :
			Trouver la ligne PATH=... dans envp.
			Découper la valeur (/usr/local/bin:/usr/bin:/bin:...) avec ft_split (":").
			Pour chaque dossier, construire dir + "/" + cmd (/bin/ls, /usr/bin/ls, …).
			Vérifier avec access(path, X_OK) si le fichier existe et est exécutable.
			Retourner le premier trouvé.

	exemples :
			char *args[] = {"ls", "-l", "-a", NULL};
			execve("/bin/ls", args, envp);

			char *args[] = {"echo", "hello", NULL};
			execve("/bin/echo", args, envp);

*/