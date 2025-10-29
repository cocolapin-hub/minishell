
#include "../minishell.h"

void	free_args(char **args)
{
	int	x;

	x = 0;

	if (!args)
		return;

	while (args[x])
		free(args[x++]);

	free(args);
}
