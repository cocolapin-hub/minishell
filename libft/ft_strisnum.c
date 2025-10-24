
#include "../minishell.h"

int	ft_strisnum(const char *str)
{
	int	x;

	x = 0;
	if (str[x] == '+' || str[x] == '-')
		x++;
	if (!str[x])
		return (0);
	while (str[x])
	{
		if ((str[x] >= '0' && str[x] <= '9'))
			x++;
		else
			return (0);
	}
	return (1);
}
