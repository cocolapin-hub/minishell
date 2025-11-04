/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:50:52 by ochkaoul         ###   ########.fr       */
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

void	type_assignation(char *content, t_type *type)
{
	if (content[0] == '|' && !content[1])
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

t_token	*ft_lstnew_token(char *content, char quote)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = content;
	type_assignation(content, &node->type);
	quotes_assignation(quote, &node->amount);
	node->next = NULL;
	return (node);
}
