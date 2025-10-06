
#include "../minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	ft_putendl_fd("coucou biche avec saut de ligne", 1);
	return (0);
}
*/
