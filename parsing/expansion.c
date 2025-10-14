
#include "../minishell.h"

char 	*split_for_expansion(char *str, char *key, int start, char *key_value)
{
    char *split1 = NULL;
    char *split2 = NULL;
    char *split3 = NULL;
    char *tmp;
    char *result;
    size_t key_len;
    size_t str_len;

    if (ft_strcmp(key, "$?") == 0 || ft_strcmp(key, "$$") == 0)
		key_len = strlen(key);
	else
		key_len = strlen(key) + 1;  // +1 pour le $

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
    result = ft_strjoin(tmp, split3);


    // free(split1);
    // free(split2);
    // free(split3);
    // free(tmp);
    // free(str);
    return (result);
}

int handle_exit_status(char **str, int last_status, int x)
{
    char *status = ft_itoa(last_status);
	int len;

	status = ft_itoa(last_status);
    *str = split_for_expansion(*str, "$?", x, status);
    len = ft_strlen(status);
    free(status);
    return (x + len);
}

int		handle_pid(char **str, int x)
{
	char	*pid;

	pid = ft_itoa(getpid());
	*str = split_for_expansion(*str, "$$", x, pid);

	return (free(pid), x + 1); //ft_strlen(pid));
}

void	get_variable_name(char *str, char *var_name, int *var_len, int *x)
{
	char c;
	*var_len = 0;
	(*x)++; 			//skip the $

	while (str[*x] && (ft_isalnum(str[*x]) || str[*x] == '_'))
	{
		if (str[*x] == 32 || str[*x] == 39)
			c = str[*x];

		var_name[*var_len] = str[*x];
		(*var_len)++;
		(*x)++;
		if (str[*x] == c)
			break ;
	}
	var_name[*var_len] = '\0';
}

int	find_variable_in_env(t_local *env, int start, char **str, char *var_name)
{
	int found;
	int x ;

	found = 0;
	x = start;
	while (env)
	{
		if (strcmp(env->key, var_name) == 0)
		{
			*str = split_for_expansion(*str, var_name, start, env->value);
			x = start + strlen(env->value);
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

char *clean_after_expansion(char *str)
{
	char 	*new_line;
	int		len;
	int 	x;
	int 	y;


	len = ft_strlen(str);
	new_line = malloc(sizeof(char) * len + 1);
	if (!new_line)
		return (NULL);

	y = 0;
	x = 0;
	while(str[x])
	{
		/*handles double spacing and tab*/
		if ((x != 0 && str[x] == 32 && str[x - 1] == 32)
		|| (x != 0 && str[x] == 9 && str[x - 1] == 9))
			x++;

		/*normal copy*/
		else
			new_line[y++] = str[x++];
	}

	new_line[y] = '\0';
	return (new_line);
}


char *expansion(t_local *env, int last_status, char *str, int x)
{
	char 	var_name[1024];
	char	*expand;
	int 	var_len;
    int 	start;

    x = 0;
    while(str[x])
    {
        if (str[x] == '$')
        {
            // Handle $?
            if (str[x + 1] == '?')
            {
                x = handle_exit_status(&str, last_status, x);
                continue ;
            }
			// Handle $$
			else if (str[x + 1] == '$')
			{
				x = handle_pid(&str, x);
				continue ;
			}

			else if (ft_isalnum(str[x + 1]) || str[x + 1] == '_')
			{
				// Extract variable name before $
				start = x;

				// Get the variable name (alphanumeric + underscore)
				get_variable_name(str, var_name, &var_len, &x);

				// Just a $ with nothing after
				if (var_len == 0)
					continue ;

				// Search for this variable in the environment
				x = find_variable_in_env(env, start, &str, var_name);
			}
			else
				x++;
		}
        else
            x++;
    }
	expand = clean_after_expansion(str);  //<-- ??
    return (expand);
}

