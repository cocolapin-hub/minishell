#include "../minishell.h"

int ft_strisnum(const char *str)
{
	int x = 0;

	if (str[x] == 43 || str[x] == 45)
		x++;
	while (str[x])
	{
		if ((str[x] >= 48 && str[x] <= 57))
			x++;
		else
			return (0);
	}

	return (1);
}