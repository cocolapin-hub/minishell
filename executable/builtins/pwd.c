
#include "../../minishell.h"

int	builtin_pwd(t_shell *all)
{
	char	cwd[MAX_LINE_LEN];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)	// toujours utiliser getcwd pour avoir le dossier courant
	{
		ft_putendl_fd(cwd, 1);
		all->last_status = 0;
		return (0);
	}
	pwd = get_env_value(all->env, "PWD");	// si getcwd echoue
	if (pwd && pwd[0] != '\0')
	{
		ft_putendl_fd(pwd, 1);
		all->last_status = 0;
		return (0);
	}
	ft_putendl_fd("minishell: pwd: error retrieving current directory", 2);
	all->last_status = 1;
	return (1);
}
