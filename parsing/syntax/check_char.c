/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/11 19:44:22 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*check_char(t_token *list, t_shell **all)
{
	char	c;

	c = list->value[0];
	if (c == ';' || c == '&')
	{
		if (list->value[0] == c && list->value[1] == c)
		{
			write(2, "syntax error near unexpected token `", 36);
			write(2, list->value, 2);
			write(2, "'\n", 2);
			(*all)->last_status = 2;
			return (NULL);
		}
	}
	return (list);
}

static void	print_syntax_error(char c, t_shell *all)
{
	write(2, "syntax error near unexpected token `", 36);
	write(2, &c, 1);
	write(2, "'\n", 2);
	all->last_status = 2;
}

static int	check_elem_special(t_token *elem, t_shell *all)
{
	char	s;

	if (!elem || !elem->value)
		return (1);
	s = ft_strbrk(elem->value, ";&{}[]()*?!");
	if (s && elem->amount == Q_NONE)
	{
		print_syntax_error(s, all);
		return (0);
	}
	return (1);
}

static int	check_args_special(char **args, int is_built, t_shell *all)
{
	char	s;
	int		i;

	if (!args || is_built)
		return (1);
	i = 0;
	while (args[i])
	{
		s = ft_strbrk(args[i], ";&{}[]()*?!");
		if (s)
		{
			print_syntax_error(s, all);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_special(t_command *cmd, t_shell *all)
{
	int	is_built;

	if (!cmd)
		return (1);
	while (cmd)
	{
		is_built = is_builtin((cmd->args[0]));
		if (!check_elem_special(cmd->elem, all))
			return (0);
		if (!check_args_special(cmd->args, is_built, all))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
