
#include "../../minishell.h"

static char	*dup_value_or_empty(char *value)
{
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static void	update_existing_var(t_local *cur, char *value)
{
	free(cur->value);
	cur->value = dup_value_or_empty(value);
}

static void	add_new_var(t_local **env, char *key, char *value)
{
	t_local	*new;

	new = malloc(sizeof(t_local));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = dup_value_or_empty(value);
	new->next = *env;
	*env = new;
}

void	set_env_value(t_local **env, char *key, char *value)
{
	t_local	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (update_existing_var(cur, value));
		cur = cur->next;
	}
	add_new_var(env, key, value);
}
