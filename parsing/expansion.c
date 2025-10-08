
#include "../minishell.h"

char *split_for_expansion(char *str, char *key, int start, char *key_value)
{
    char *split1 = NULL;
    char *split2 = NULL;
    char *split3 = NULL;
    char *tmp;
    char *result;
    size_t key_len;
    size_t str_len;

    if (strcmp(key, "$?") != 0)
        key_len = strlen(key) + 1;  // +1 fpour le $
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
    result = ft_strjoin(tmp, split3);


    // free(split1);
    // free(split2);
    // free(split3);
    // free(tmp);
    // free(str);
    return (result);
}



char *expansion(t_local *env, int last_status, char *str, int x)
{
	char 	var_name[1024];
	int 	var_len;
    char	*status;
	int		found;
    int 	start;
	t_local *env2;


    x = 0;
    while(str[x])
    {
        if (str[x] == '$')
        {
            // Handle $?
            if (str[x + 1] == '?')
            {
                status = ft_itoa(last_status);
                str = split_for_expansion(str, "$?", x, status);
                free(status);
                x = 0;  											// Restart from beginning
                continue ;
            }

            // Extract variable name after $
            start = x;
            var_len = 0;
            x++;  // Skip the $

            // Get the variable name (alphanumeric + underscore)
            while (str[x] && (ft_isalnum(str[x]) || str[x] == '_'))
                var_name[var_len++] = str[x++];
            var_name[var_len] = '\0';

            if (var_len == 0)  										// Just a $ with nothing after
                continue ;

            // Search for this variable in the environment
            env2 = env;
            found = 0;
            while (env2)
            {
                if (strcmp(env2->key, var_name) == 0)
                {
                    str = split_for_expansion(str, var_name, start, env2->value);
                    x = start + strlen(env2->value);
                    found = 1;
                    break;
                }
                env2 = env2->next;
            }

            // Variable not found - remove $VAR_NAME
            if (!found)
            {
                str = split_for_expansion(str, var_name, start, "");
                x = start;
            }
        }
        else
        {
            x++;
        }
    }

    return str;
}
