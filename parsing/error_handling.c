/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/11 13:55:43 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token 	*check_word(t_token *list, t_SHELL **all)
{
	/*check quotes*/
	if (list->amount == Q_ERROR)
	{
		write(2, "syntax error: unclosed quote\n", 29);
		(*all)->last_status = 258;
		return NULL;
	}

	/*if it is && or ||*/
	else if ((strcmp(list->value, "||") == 0 || strcmp(list->value, "&&") == 0) && list->amount == Q_NONE)
	{
		write(2, "syntax error: unkwon character\n", 31);
		(*all)->last_status = 258;
		return NULL;
	}
	return (list);
}

t_token 	*check_pipe_and_redir(t_token *list, t_SHELL **all)
{
	const char	*token[] = {"|", "<", ">", ">>", "<<"};

	if (list->type != WORD && (list->next == NULL || list->next->type != WORD))
	{
		write(2, "syntax error near unexpected token '", 36);
		write(2, token[list->type - 1], ft_strlen(token[list->type - 1]));
		write(2, "'\n", 2);
		(*all)->last_status = 258;
		return NULL;
	}
	return (list);
}

void 	error_handling(t_SHELL **all, t_token **list)
{
	t_token *lst2 	= *list;

	while (lst2)
	{
		if (lst2->type == WORD)
			lst2 = check_word(lst2, all);

		else if (lst2->type != WORD)
			lst2 = check_pipe_and_redir(lst2, all);

		/*end if an error was caught*/
		if (!lst2)
		{
			list = NULL;
			return;
		}

		lst2 = lst2->next;
	}
}