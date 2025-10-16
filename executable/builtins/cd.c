
#include "../../minishell.h"

static void	update_pwd(t_local *env)
{
	char	cwd[MAX_LINE_LEN];
	char	*oldpwd;

	oldpwd = get_env_value(env, "PWD");		   // recup l'ancienne valeur de pwd
	if (oldpwd)
		set_env_value(&env, "OLDPWD", oldpwd); // maj de oldpwd
	if (getcwd(cwd, sizeof(cwd)))			   // recup le chemin courant apres chdir
		set_env_value(&env, "PWD", cwd);
}

int	builtin_cd(char **args, t_local **env)
{
	char *path;

	if (!args[1] || args[1][0] == '\0') 							   // no arg -> HOME
	{
		path = get_env_value(*env, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)					   // return 0 si succes, -1 si erreur
	{
		perror("minishell: cd");
		return (1);
	}
	update_pwd(*env);						   // maj de pwd et oldpwd
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


cd .. fonctionne mais ne met pas a jour PWD ni OLDPWD, mais c'est pas demandé dans l'énoncé.

*/