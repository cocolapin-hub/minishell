
#include "../minishell.h"

char	ft_strbrk(const char *s1, const char *s2)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		y = 0;
		while (s2[y])
		{
			if (s1[x] == s2[y])
				return (s2[y]);
			y++;
		}
		x++;
	}
	return (0);
}
