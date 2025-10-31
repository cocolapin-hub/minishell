
#include "../../../minishell.h"

static int	handle_variable(t_local *env, char **str, char *var_name, int start)
{
	if (!env->value)
		*str = split_expansion(*str, var_name, start, "");
	else
		*str = split_expansion(*str, var_name, start, env->value);
	return (start);
}

int	find_variable(t_local *env, int start, char **str, char *var_name)
{
	while (env)
	{
		if (strcmp(env->key, var_name) == 0)
			return (handle_variable(env, str, var_name, start));
		env = env->next;
	}
	*str = split_expansion(*str, var_name, start, "");
	return (start);
}
