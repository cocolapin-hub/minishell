
#include "../minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	size_t	x;

	if (!str)
		return ;
	x = 0;
	while (str[x])
	{
		write(fd, &str[x], 1);
		x++;
	}
}
