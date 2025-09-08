
#include "../minishell.h"

int	builtin_cd(char **args, char **envp)
{
	char *path;

	if (!args[1]) // no arg -> HOME
	{
		path = find_env_value(envp, "HOME");
		if (!path)
		{
			//write(2, "error...\n, ...);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1) // return 0 si succes, -1 si erreur
	{
		perror("minishell: cd");
		return (1);
	}
	// mise à jour de PWD/OLDPWD sera faite plus tard avec envp custom
	(void)envp;
	return (0);
}
/*

Utilise la fonction chdir(const char *path) (autorisé par le sujet).
Si l’appel échoue → afficher une erreur (perror est autorisé).

Comportements demandés par le sujet :
		cd avec un chemin absolu (/home/user) → aller directement dans ce dossier.
		cd avec un chemin relatif (../, ./mon_dossier) → interprété relativement au dossier actuel.

Si aucun argument est fourni → se référer à HOME (comme bash).
		Ça veut dire qu’il faut chercher la valeur de $HOME dans envp.
		(exemple : cd → équivaut à cd /home/claffut si $HOME=/home/claffut).

Après un changement de dossier réussi :
		mettre à jour les variables d’environnement PWD et OLDPWD.

*/