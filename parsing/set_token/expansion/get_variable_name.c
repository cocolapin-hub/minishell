
#include "../../../minishell.h"

void	get_variable_name(char *str, char *var_name, int *var_len, int *x)
{
	char	c;

	*var_len = 0;
	c = '\0';
	(*x)++;
	while (str[*x] && (ft_isalnum(str[*x]) || str[*x] == '_') && str[*x] != 61)
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
