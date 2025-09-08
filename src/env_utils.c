
#include "../minishell.h"

char	*find_env_value(char **env, const char *key)
{
	int		i;
	int		len;

	if (!env || !key)
		return (NULL);
	len = ft_strlen(key); // key = "HOME" len = 4
	i = 0;
	while (env[i]) // on parcout tous les env
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=') // "HOME=" et pas "HOMELESS="
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*make_env(const char *key, const char *value)
{

}

static int	replace_env_value(char **env, const char *key, char *new_entry)
{

}

static int	add_env_value(char **envp, char *new_entry)
{

}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}


set_env_value(char ***env, const char *key, const char *value)
{
	char	*new_entry;

	if (!env || !*env || !key || !value)
		return (1);
	new_entry = make_env(key, value);
	if (!new_entry)
		return (1);
	if (replace_env_value(*env, key, new_entry))
		return (0);
	return (add_env_value(env, new_entry));
}


unset_env_value()
{

}



/*
_____find_env_value()
Parcourir env pour voir si la clé existe déjà.
	- Chaque entrée est de la forme "KEY=VALUE".
	- Si KEY correspond → remplacer l’ancienne ligne par une nouvelle "KEY=VALUE".

Si la clé n’existe pas :
	- Calculer la taille du tableau env.
	- Allouer un nouveau tableau plus grand de 1 (pour ajouter la nouvelle variable).
	- Copier toutes les anciennes entrées dedans.
	- Ajouter la nouvelle ligne "KEY=VALUE".
	- Terminer par NULL.
	- Libérer l’ancien tableau.

Retourner 0 si succès, 1 si erreur

*/