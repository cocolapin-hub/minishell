
#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size > src_len + 1)
		ft_memcpy(dst, src, src_len + 1);
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (src_len);
}
/*
#include <stdio.h>
int	main(void)
{
        char dst[10];
        char *src = "hello";
        size_t x = 3;

        printf("%ld", ft_strlcpy((char *)dst, (char *)src, x));
}*/
