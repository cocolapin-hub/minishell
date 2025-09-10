
#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_local	*new_env_node(char *key, char *value) // duplique key et value pour éviter de modifier l’original envp.
{
	t_local	*node;

	node = malloc(sizeof(t_local));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;						 // next = NULL car c’est un maillon isolé pour l’instant.
	return (node);
}

void	add_env_node(t_local **env, t_local *new_node)
{
	t_local	*tmp;

	if (!env || !new_node)
		return ;
	if (!*env) 			  // Si la liste est vide
	{
		*env = new_node;  // le nouveau devient la tête.
		return ;
	}
	tmp = *env;
	while (tmp->next)	  // on parcourt jusqu’au dernier
		tmp = tmp->next;
	tmp->next = new_node; // et on relie
}

t_local	*env_init(char **envp)
{
	t_local	*env;
	t_local	*node;
	int		i;
	char	*eq;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '='); 			  // strchr pointe vers sur '='
		if (eq)
		{
			*eq = '\0'; 						  // coupe la string "PATH=/bin" -> "PATH" et "/bin"
			node = new_env_node(envp[i], eq + 1); // crée node {key=PATH, value=/bin}
			*eq = '='; 							  // remet le '=' pour pas casser envp original
			add_env_node(&env, node);
		}
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_local	*env;

	(void)argc;
	(void)argv;
	env = env_init(envp);

	// debug: afficher les premières variables
	t_local *tmp = env;
	while (tmp && tmp->next)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}






/*
 readline → pour lire la ligne.
 find_in_path → pour trouver la commande.
 exec_command → pour exécuter.
*/













