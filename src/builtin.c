
#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[4096]; // buffer pour stocker le chemin absolu ecrit depuis getcwd

	if (getcwd(cwd, sizeof(cwd)) != NULL) // si ca echoue return NULL donc appelle perror
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}