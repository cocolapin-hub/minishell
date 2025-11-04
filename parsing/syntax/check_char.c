/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:53:58 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*check_char(t_token *list, t_shell **all)
{
	char	c;
	char	s;

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
	s = ft_strbrk(list->value, ":;&{}[]()*?!");
	if (s)
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &s, 1);
		write(2, "'\n", 2);
		(*all)->last_status = 2;
		return (NULL);
	}
	return (list);
}
