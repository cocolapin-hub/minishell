
#include "../../minishell.h"

static void	update_pwd(t_local **env)
{
	char	cwd[MAX_LINE_LEN];
	char	*oldpwd;

	oldpwd = get_env_value(*env, "PWD");
	if (oldpwd)
		set_env_value(env, "OLDPWD", oldpwd);
	else
		unset_env_value(env, "OLDPWD");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putendl_fd("minishell: cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2);
		unset_env_value(env, "PWD");
		return ;
	}
	set_env_value(env, "PWD", cwd);
}

static int	cd_error(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Not a directory", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (1);
}

int	builtin_cd(char **args, t_local **env)
{
	char	*path;

	if (args[2] && args[2][0] != '\0')
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (!args[1] || args[1][0] == '\0')
	{
		path = get_env_value(*env, "HOME");
		if (!path)
			return (write(2, "minishell: cd: HOME not set\n", 28), 1);
		if (path[0] == '\0')
			return (0);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
		return (cd_error(path), 1);
	update_pwd(env);
	return (0);
}
/*
(chdir(path) == -1)	   // return 0 si succes, -1 si erreur
Utilise la fonction chdir(const char *path) (autorisé par le sujet).
Si l’appel échoue → afficher une erreur (perror est autorisé).

*/