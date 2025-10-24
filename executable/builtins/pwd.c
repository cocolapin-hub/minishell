
#include "../../minishell.h"

int	builtin_pwd(void)
{
	char	cwd[MAX_LINE_LEN];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putendl_fd("minishell: pwd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2);
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
