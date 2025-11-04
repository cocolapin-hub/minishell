/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:44:05 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_unset_error(char *arg)
{
	write(2, "unset: `", 8);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

static void	handle_unset_arg(char *arg, t_local **env)
{
	if (!is_valid_identifier(arg))
	{
		print_unset_error(arg);
		return ;
	}
	if (ft_strcmp(arg, "_") == 0)
		return ;
	unset_env_value(env, arg);
}

int	builtin_unset(char **args, t_local **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		handle_unset_arg(args[i], env);
		i++;
	}
	return (0);
}

/*
Parcours la liste chaînée.
Si cur->key correspond à la clé à supprimer → on relie le précédent au suivant.
Free les champs key et value + le maillon lui-même.
*/