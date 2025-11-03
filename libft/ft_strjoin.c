
#include "../minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	int		x;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	x = 0;
	while (s1[x])
	{
		str[x] = s1[x];
		x++;
	}
	y = 0;
	while (s2[y])
	{
		str[x + y] = s2[y];
		y++;
	}
	str[x + y] = 0;
	return (str);
}
