
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		(void)*(s++);
	}
	if ((char) c == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char *str= "hello word";

	printf("%s", ft_strchr((char *) str, 'o'));


}*/
