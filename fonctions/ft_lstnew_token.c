/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:59:43 by claffut           #+#    #+#             */
/*   Updated: 2025/09/05 15:45:28 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes_assignation(char quotes, t_quote *amount)
{
	if (quotes == 34)
		*amount = Q_DOUBLE;
	else if (quotes == 39)
		*amount = Q_SINGLE;
	else
		*amount = Q_NONE;
}

void	type_assignation(char *content, t_element *type)
{
	if (content[0] ==  '|' && !content[1])
		*type = PIPE;

	else if (content[0] == '<' && !content[1])
		*type = REDIR_IN;

	else if (content[0] == '>' && !content[1])
		*type = REDIR_OUT;

	else if (content[0] == '>' && content[1] == '>' && !content[2])
		*type = REDIR_APPEND;

	else if (content[0] == '<' && content[1] == '<' && !content[2])
		*type = REDIR_HEREDOC;

	else
		*type = WORD;
}

t_token	*ft_lstnew_token(char *content, char quotes)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		exit (1);

	/*content*/
	node->value = content;

	/*element*/
	type_assignation(content, &node->type);

	/*content*/
	quotes_assignation(quotes, &node->amount);

	node->next = NULL;
	return (node);
}
