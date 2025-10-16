
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


// int	builtin_pwd(void)
// {
// 	char	cwd[MAX_LINE_LEN]; 			  // buffer pour stocker le chemin absolu ecrit depuis getcwd (current work directory)

// 	if (getcwd(cwd, sizeof(cwd)) != NULL) // si ca echoue return NULL donc appelle perror
// 	{
// 		// printf("%s\n", cwd);
// 		ft_putendl_fd(cwd, 1);
// 		return (0);
// 	}
// 	perror("minishell: pwd");
// 	return (1);
// }
