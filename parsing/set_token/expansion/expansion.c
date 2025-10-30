
#include "../../../minishell.h"

static int	handle_special_expansion(int *x, char **str, int last_status)
{
	// Handle $?
	if ((*str)[*x + 1] == '?')
	{
		*x = handle_exit_status(str, last_status, *x);
		return (0);
	}

	// Handle $$
	else if ((*str)[*x + 1] == '$')
	{
		*x = handle_pid(str, *x);
		return (0);
	}

	//handle number
	else if ((*str)[*x + 1] >= 48 && (*str)[*x + 1] <= 57)
	{
		if ((*str)[*x + 1] != '0')
			*x = handle_numbers(str, *x);
		else
			*x = handle_number_zero(str, *x);
		return (0);
	}
	return 1;
}

static int handle_normal_expansion(int *x, char **str, t_local *env)
{
    char    var_name[1024] = {0};
    int     var_len = 0;
    int     start;
    int     saved_x;

    if (ft_isalnum((*str)[*x + 1]) || (*str)[*x + 1] == '_')
    {
        start = *x;
        saved_x = *x;
        get_variable_name(*str, var_name, &var_len, x);
        if (var_len == 0)
            return (0);
        *x = find_variable_in_env(env, start, str, var_name);
        if (*x == start)
            *x = start;
        return (0);
    }
    return (1);
}

static int	handle_expansion(int *x, char **str, t_local *env, int last_status)
{
	if (handle_normal_expansion(x, str, env) == 0)
		return (0);

	else if (handle_special_expansion(x, str, last_status) == 0)
		return (0);

	else
		return (1);
}

static char *wrap_up_expansion(char *expand, int expansion_done, char *quote, char *str)
{
	if (expansion_done == 1 && (!quote || *quote == 0))
		expand = clean_after_expansion(str);
    else
		expand = ft_strdup(str);

	free(str);
	return (expand);
	}

	char *expansion(t_local *env, int last_status, char *str, char *quote)
	{
		int     expansion_done;
		char    *expand = NULL;
		int     x;

		expansion_done = 0;
		x = 0;
		while(str[x] && str[x] != 61)
		{
			if (str[x] == '$')
			{
				expansion_done = 1;
				if (handle_expansion(&x, &str, env, last_status) == 0)
                continue ;
				else
                x++;
			}
			else
            x++;
		}

    expand = wrap_up_expansion(expand, expansion_done, quote, str);
    return expand;
}

