#include "../minishell.h"

static t_local	*new_env_node(char *key, char *value)
{
	t_local	*node;

	node = malloc(sizeof(t_local));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

static void	add_env_node(t_local **env, t_local *new_node)
{
	t_local	*tmp;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_local	*env_init(char **envp, t_shell *all)
{
	t_local	*node;
	t_local	*env;
	char	*eq;
	int		i;

	all->last_status = 0;
	all->sig_type = 0;
	env = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			*eq = '\0'; 						  /* coupe la string "PATH=/bin" -> "PATH" et "/bin"*/
			node = new_env_node(envp[i], eq + 1); // crée node {key=PATH, value=/bin}
			*eq = '='; 							  // remet le '=' pour pas casser envp original
			add_env_node(&env, node);
		}
		i++;
	}
	return (env);
}
