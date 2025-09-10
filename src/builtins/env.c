#include "../minishell.h"

int	builtin_env(t_local *env)
{
	t_local	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value) // afficher uniquement les variables avec une valeur
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
Afficher toutes les variables d’environnement actuelles dans la liste chaînée t_env.
Pas de modification, pas d’argument à gérer.
*/