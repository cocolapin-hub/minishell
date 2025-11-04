/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outside_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:53:36 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	expand_word(char **tmp, char quote, t_shell **all, t_token **list)
{
	t_token	*last;

	last = NULL;
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}
	if (!last || last->type != REDIR_HEREDOC)
		*tmp = expansion((*all)->env, (*all)->last_status, *tmp, &quote);
}

char	*outside_quotes(char *line, int *x, t_shell **all, t_token **list)
{
	int		start;
	char	*tmp;
	int		y;

	tmp = NULL;
	y = *x;
	if (line[y] == '$' && (line[y + 1] == 34 || line[y + 1] == 39))
	{
		(*x)++;
		return (tmp = ft_strdup(""));
	}
	else
	{
		start = find_word(&y, *x, line, &tmp);
		if (!tmp)
			return (NULL);
		expand_word(&tmp, 0, all, list);
	}
	if (line[start] == '$' && ft_strcmp(tmp, "") == 0)
	{
		*x = y;
		return (free(tmp), skip());
	}
	*x = y;
	return (tmp);
}
