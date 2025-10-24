
#include "../minishell.h"

char	*ft_strdup_m(const char *s, int x, int len)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		exit (1);
	i = 0;
	while (len != 0)
	{
		copy[i++] = s[x++];
		len--;
	}
	copy[i] = '\0';
	return (copy);
}
/*
#include <stdio.h>
#include <string.h>


char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	x;

	dst = (char *)malloc(ft_strlen(s) + 1);
	if (!dst)
		return (NULL);
	x = 0;
	while (s[x])
	{
		dst[x] = s[x];
		x++;
	}
	dst[x] = 0;
	return (dst);
}

int	main(void)
{
	const char *src = "Salut les copains !";

	char *dup1 = ft_strdup(src);
	char *dup2 = strdup(src);

	printf("ft_strdup : %s\n", dup1);
	printf("strdup    : %s\n", dup2);

	free(dup1);
	free(dup2);

	return 0;
}
*/