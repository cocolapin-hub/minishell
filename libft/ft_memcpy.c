
#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (!dst && !src)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (n > 0)
	{
		*(tmp_dst++) = *(tmp_src++);
		n--;
	}
	return (dst);
}
/*
#include <stdio.h>

int	main(void)
{
	char dst[10];
	char *src = "hello";
	size_t x = 3;

	ft_memcpy((char *)dst, (char *)src, x);
	dst[x] = 0;
	printf("%s", dst);
}*/
