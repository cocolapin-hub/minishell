#include "../../../minishell.h"


int		find_variable_in_env(t_local *env, int start, char **str, char *var_name)
{
	int found;
	int x ;

	found = 0;
	x = start;
	while (env)
	{
		if (strcmp(env->key, var_name) == 0)
		{
			if (!env->value)
			{
				*str = split_for_expansion(*str, var_name, start, "");
				x = start;
				return (x);
			}
			else
			{
				*str = split_for_expansion(*str, var_name, start, env->value);
				x = start + strlen(env->value);
			}
			found = 1;
			break;
		}
		env = env->next;
	}
	if (!found)
	{
		*str = split_for_expansion(*str, var_name, start, "");
		x = start;
	}
	return (x);
}