
#include "../minishell.h"

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
/*
#include <stdio.h>

int	main(void)
{
	printf("%s", ft_strdup("mari"));


}*/
