/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:51:54 by claffut           #+#    #+#             */
/*   Updated: 2025/09/02 18:27:12 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_line(char **envp)
{
	
}

char	*build_path(char *dir, char *cmd)
{
	
}

void	free_split(char **array)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_in_path(char *cmd, char **envp)
{
	
}



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

