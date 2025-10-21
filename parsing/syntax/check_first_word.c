#include "../../minishell.h"


t_token		*check_first_word(t_token *list, t_shell **all)
{
	int		counter;
	int 	x;

	counter = 0;
	x = 0;

	//is_a_directory
	if (list && list->type == WORD)
	{
		while (list->value[x])
		{
			if (list->value[x] == '.' || list->value[x] == '/')
			{
				if (list->value[x] == '.')
					counter++;
				else
					counter = 0;
				if (counter > 2)
					return (list);
				x++;
			}
			else
				break ;
			if (list->value[x] == '\0')
			{
				write(2, list->value, ft_strlen(list->value));
				write(2, ": Is a directory\n", 17);
				(*all)->last_status = 126;
				return NULL;
			}
		}
	}

	return (list);
}
