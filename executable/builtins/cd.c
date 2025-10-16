
#include "../../minishell.h"

static void	update_pwd(t_local **env)	//	ANCIENNE VERSION QUI MET AJOUR PWD QUOI QUIL ARRIVE
{
	char	cwd[MAX_LINE_LEN];		// current working directory
	char	*oldpwd;
	int		pwdexist;

	oldpwd = get_env_value(*env, "PWD");		   // recup l'ancienne valeur de pwd
	if (oldpwd)
		set_env_value(env, "OLDPWD", oldpwd); // maj de oldpwd
	else
		unset_env_value(env, "OLDPWD");
	pwdexist = getcwd(cwd, sizeof(cwd)) != NULL;
	if (pwdexist)
		set_env_value(env, "PWD", cwd);
	else
	{
		unset_env_value(env, "PWD");
		unset_env_value(env, "OLDPWD");
	}
}

// static void	update_pwd(t_local **env)
// {
// 	char	cwd[MAX_LINE_LEN];
// 	char	*oldpwd;
// 	t_local	*pwd_node;
// 	t_local	*oldpwd_node;

// 	pwd_node = find_env_key(*env, "PWD");
// 	oldpwd_node = find_env_key(*env, "OLDPWD");
// 	if (oldpwd_node)	// Si OLDPWD existe, on le met à jour avec l'ancienne valeur de PWD
// 	{
// 		oldpwd = NULL;
// 		if (pwd_node && pwd_node->value)
// 			oldpwd = pwd_node->value;
// 		if (oldpwd)
// 		{
// 			free(oldpwd_node->value);
// 			oldpwd_node->value = ft_strdup(oldpwd);
// 		}
// 		else
// 		{
// 			if (oldpwd_node->value)
// 			{
// 				free(oldpwd_node->value);
// 				oldpwd_node->value = NULL;
// 			}
// 		}
// 	}
// 	if (pwd_node && getcwd(cwd, sizeof(cwd)))	// Si PWD existe, on le met à jour avec le répertoire courant
// 	{
// 		free(pwd_node->value);
// 		pwd_node->value = ft_strdup(cwd);
// 	}
// }

static int	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int	builtin_cd(char **args, t_local **env)
{
	char *path;

	if (args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (!args[1] || args[1][0] == '\0') 	   // no arg -> HOME
	{
		path = get_env_value(*env, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)					   // return 0 si succes, -1 si erreur
	{
		cd_error(path);
		return (1);
	}
	update_pwd(env);						   // maj de pwd et oldpwd
	return (0);
}
/*

Utilise la fonction chdir(const char *path) (autorisé par le sujet).
Si l’appel échoue → afficher une erreur (perror est autorisé).

*/