
#include "../minishell.h"

char		*split_for_expansion(char *str, char *key, int start, char *key_value)
{
	char 	*split1 = NULL;
	char 	*split2 = NULL;
	char 	*split3 = NULL;
	char 	*tmp;
	size_t 	key_len;
	size_t	str_len;

	if (strcmp(key, "$?") != 0)
		key_len = strlen(key) + 1;
	else
		key_len = strlen(key);

	str_len = strlen(str);

	if (start == 0)
		split1 = ft_strdup("");
	else
		split1 = ft_strdup_m(str, 0, start);

	split2 = ft_strdup(key_value);

	if (start + key_len < str_len)
		split3 = ft_strdup_m(str, start + key_len, str_len - (start + key_len));
	else
		split3 = ft_strdup("");

	tmp = ft_strjoin(split1, split2);
	str = ft_strjoin(tmp, split3);

	free(split2);
	free(split3);
	return (str);
}


char		*expansion(t_local *env, int last_status, char *str, int x)
{
	char		*status;
	t_local 	*env2;
	int			start;

	env2 = env;
	start = 0;
	while(str[x])
	{
		if (str[x] == '$' && str[x + 1] == '?')
		{
			status = ft_itoa(last_status);
			str = split_for_expansion(str, "$?", x, status);
			free(status);
			x = 0;
			continue ;
		}
		else
		{
			start = ft_strstr(str, env2->key) - 1;
			if (start > -1)
			{
				str = split_for_expansion(str, env2->key, start, env2->value);
				x = start + strlen(env2->value);
				env2 = env;
				continue ;
			}
			env2= env2->next;
		}
		x++;
	}
	return str;
}



