

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (s[x])
		x++;
	return (x);
}

/*#include <stdio.h>

int	main(void)
{
	const char *x= "hello";
	printf("%zu", ft_strlen(x));
}*/
