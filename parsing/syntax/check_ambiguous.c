/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 18:07:33 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ==12062== Invalid read of size 4
// ==12062==    at 0x407493: check_ambiguous (check_ambiguous.c:31)
// ==12062==    by 0x405C6B: parse (handles_command.c:39)
// ==12062==    by 0x405D66: handles_command (handles_command.c:61)
// ==12062==    by 0x40639F: tokenisation (tokenisation.c:27)
// ==12062==    by 0x404EDB: parsing (parsing.c:36)
// ==12062==    by 0x4013D5: main (main.c:44)
// ==12062==  Address 0x0 is not stack'd, malloc'd or (recently) free'd

int	check_ambiguous(char *line, int x, t_token **list, t_shell **all)
{
	t_token	*last;
	char	*tmp;
	int		y;

	last = NULL;
	tmp = NULL;
	y = x;
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}
	find_word(&y, x, line, &tmp);
	if (last)
	{
		if (last->type == REDIR_IN && ft_strcmp(tmp, "") != 0)
		{
			write(1, tmp, ft_strlen(tmp));
			write(1, ": ambiguous redirect\n", 21);
			(*all)->last_status = 1;
			return (free(tmp), 1);
		}
	}
	return (free(tmp), 0);
}
