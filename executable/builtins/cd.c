/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 20:48:32 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_putendl_fd("cd: error retrieving current directory: \
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
		print_err("cd", path, "Not a directory");
	else
		print_err("cd", path, strerror(errno));
	return (1);
}

static int	cd_oldpwd(t_local **env)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_env_value(*env, "OLDPWD");
	if (!oldpwd)
		return (print_err("cd", NULL, "OLDPWD not set"), 1);
	if (chdir(oldpwd) == -1)
		return (cd_error(oldpwd), 1);
	update_pwd(env);
	newpwd = get_env_value(*env, "PWD");
	if (newpwd)
		ft_putendl_fd(newpwd, 1);
	return (0);
}

int	builtin_cd(char **args, t_local **env)
{
	char	*path;
	int		argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc > 2)
		return (print_err("cd", NULL, "too many arguments"), 1);
	if (argc == 1 || (argc == 2 && args[1][0] == '\0'))
	{
		path = get_env_value(*env, "HOME");
		if (!path)
			return (print_err("cd", NULL, "HOME not set"), 1);
		if (path[0] == '\0')
			return (0);
	}
	else if (ft_strcmp(args[1], "-") == 0)
		return (cd_oldpwd(env));
	else
		path = args[1];
	if (chdir(path) == -1)
		return (cd_error(path), 1);
	update_pwd(env);
	return (0);
}
