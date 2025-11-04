/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:44:02 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(t_shell *all)
{
	char	cwd[MAX_LINE_LEN];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, 1);
		all->last_status = 0;
		return (0);
	}
	pwd = get_env_value(all->env, "PWD");
	if (pwd && pwd[0] != '\0')
	{
		ft_putendl_fd(pwd, 1);
		all->last_status = 0;
		return (0);
	}
	ft_putendl_fd("pwd: error retrieving current directory", 2);
	all->last_status = 1;
	return (1);
}
