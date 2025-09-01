/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:59 by claffut           #+#    #+#             */
/*   Updated: 2025/04/23 13:07:51 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*safe_lstnew(void *content, void (*del)(void *))
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
	{
		del(content);
		return (NULL);
	}
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node = safe_lstnew(new_content, del);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*duplicate(void *content)
{
	return (ft_strdup((char *)content));
}

void	del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*lst = ft_lstnew(ft_strdup("un"));
	t_list	*new_lst;
	t_list	*tmp;

	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("deux")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("trois")));

	new_lst = ft_lstmap(lst, duplicate, del);

	tmp = new_lst;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}

	ft_lstclear(&lst, del);
	ft_lstclear(&new_lst, del);

	return (0);
}
*/