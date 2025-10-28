
#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char *result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
