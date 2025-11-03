
#include "../../../minishell.h"

int	handle_pid(char **str, int x)
{
	char	*pid;
	int		len;

	pid = ft_itoa(getpid());
	len = ft_strlen(pid);
	*str = split_expansion(*str, "$$", x, pid);
	free(pid);
	return (x + len);
}
