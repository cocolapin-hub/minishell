#include "../minishell.h"

int	builtin_unset(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env_value(&env, args[i]);
		i++;
	}
	return (0);
}

/*
Parcours la liste chaînée.
Si cur->key correspond à la clé à supprimer → on relie le précédent au suivant.
Free les champs key et value + le maillon lui-même.
*/