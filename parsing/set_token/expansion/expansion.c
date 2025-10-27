
#include "../../../minishell.h"


char 	*clean_after_expansion(char *str)
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


char 	*expansion(t_local *env, int last_status, char *str, char *quote)
{
	char 	var_name[1024];
	char	*expand;
	int 	var_len;
    int 	start;
	int		expansion_done;
	int		x;

	expansion_done = 0;
    x = 0;
    while(str[x] && str[x] != 61)
    {
        if (str[x] == '$')
        {
			expansion_done = 1;

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

			// // handle number
			else if (str[x + 1] >= 48 && str[x + 1] <= 57)
			{
				if (str[x + 1] != '0')
					x = handle_numbers(&str, x);
				else
					x = handle_number_zero(&str, x);
				continue ;
			}

			//handle $VAR
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
	if (expansion_done == 1 && !quote)
		expand = clean_after_expansion(str);  //<-- ??
    else
		expand = ft_strdup(str);
	return (expand);
}

