/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   between_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/05 18:59:04 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	expand_word(char **tmp, char quote, t_shell **all, t_token **list)
{
	char	*expanded;
	t_token	*last;

	last = NULL;
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}
	if (quote == 39 || (last && last->type == REDIR_HEREDOC))
		return ;
	expanded = expansion((*all)->env, (*all)->last_status, tmp, &quote);
	if (!expanded)
	{
		free(*tmp);
		*tmp = NULL;
		return ;
	}
	*tmp = expanded;
}

char	*between_quotes(char *line, int *x, t_shell **all, t_token **list)
{
	char	quote;
	char	*tmp;
	int		y;

	y = *x + 1;
	quote = line[*x];
	if (line[y] == quote)
	{
		*x += 2;
		return (tmp = ft_strdup(""));
	}
	while (line[y] && line[y] != quote)
		y++;
	if (line[y] == '\0')
	{
		write(2, "syntax error: unclosed quotes\n", 30);
		(*all)->last_status = 258;
		return (NULL);
	}
	tmp = ft_strdup_m(line, *x + 1, y - *x - 1);
	if (!tmp)
		return (NULL);
	expand_word(&tmp, quote, all, list);
	*x = y + 1;
	return (tmp);
}
