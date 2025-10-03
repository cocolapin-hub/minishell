
#include "../minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*tmp;
	size_t		total;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb > (SIZE_MAX / size) && size != 0)
		return (NULL);
	total = nmemb * size;
	tmp = (char *)malloc(total);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, total);
	return (tmp);
}
/*
#include <stdio.h>
#include <limits.h>
int main()
{
	char *test;

	test = NULL;
	test = ft_calloc(4294967295, 4294967295);
	// printf("%s\n", test);
	return 0;
}*/
