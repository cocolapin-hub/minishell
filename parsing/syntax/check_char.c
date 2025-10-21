#include "../../minishell.h"


t_token 	*check_char(t_token *list, t_shell **all)
{
	char c;
	char s;


	/*if it is many ; et &*/
	c = list->value[0];
	if (c == ';' || c == '&')
	{
		if (list->value[0] == c && list->value[1] == c)
		{
			write(2, "syntax error near unexpected token `", 36);
			write(2, list->value, 2);
			write(2, "'\n", 2);
			(*all)->last_status = 2;
			return (NULL);
		}
	}

	/*if it is one ; et &*/
	s = ft_strbrk(list->value, ";&{}[]()*?!");
	if (s)
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &s , 1);
		write(2, "'\n", 2);
		(*all)->last_status = 2;
		return (NULL);
	}

	return (list);
}
