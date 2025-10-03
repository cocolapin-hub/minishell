#include "../minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	joined = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	free(s1);
	return (joined);
}
/*
if (!joined)
	return (free(s1), NULL);

joined[i + j] = '\0';
free(s1);
return (joined);

#include <stdio.h>

int	main(void)
{
	char *joined = ft_strjoin("lol, ", "mdr!");
	printf("ft_strjoin : %s\n", joined);
	free(joined);
	return 0;
}
*/