
#include "../minishell.h"

char	*ft_strdup_m(const char *s, int x, int len)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (len != 0)
	{
		copy[i++] = s[x++];
		len--;
	}
	copy[i] = '\0';
	return (copy);
}
