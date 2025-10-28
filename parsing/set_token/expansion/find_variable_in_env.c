
#include "../../../minishell.h"

static int	handle_found_variable(t_local *env, char **str, char *var_name, int start)
{
	int	x;

	if (!env->value)
	{
		*str = split_for_expansion(*str, var_name, start, "");
		x = start;
	}
	else
	{
		*str = split_for_expansion(*str, var_name, start, env->value);
		x = start + strlen(env->value);
	}
	return (start);
}

int	find_variable_in_env(t_local *env, int start, char **str, char *var_name)
{
	int	x;

	x = start;
	while (env)
	{
		if (strcmp(env->key, var_name) == 0)
			return (handle_found_variable(env, str, var_name, start));
		env = env->next;
	}
	*str = split_for_expansion(*str, var_name, start, "");
	return (start);
}
