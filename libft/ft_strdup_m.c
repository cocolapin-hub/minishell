/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/05 17:33:32 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_m(const char *s, int x, int len)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (len != 0)
	{
		copy[i++] = s[x++];
		len--;
	}
	copy[i] = '\0';
	return (copy);
}
