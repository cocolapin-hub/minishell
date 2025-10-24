
#include "../../minishell.h"

char	*get_env_value(t_local *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_local	*find_env_key(t_local *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	unset_env_value(t_local **env, char *key)
{
	t_local	*prev;
	t_local	*cur;

	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	sort_env_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_var(char *var)
{
	char	*equal;

	equal = ft_strchr(var, '=');
	if (equal)
	{
		*equal = '\0';
		ft_putstr_fd(var, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(equal + 1, 1);
		ft_putendl_fd("\"", 1);
		*equal = '=';
	}
	else
		ft_putendl_fd(var, 1);
}
