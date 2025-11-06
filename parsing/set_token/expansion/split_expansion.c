/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 17:50:34 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	free_splits(char **splits)
{
	if (splits)
	{
		free(splits[0]);
		free(splits[1]);
		free(splits[2]);
		free(splits);
	}
}

static char	**make_splits(char *str, char *key, int start, char *key_value)
{
	size_t	k_len;
	size_t	s_len;
	char	**splits;

	splits = malloc(sizeof(char *) * 3);
	if (!splits)
		return (NULL);
	if (key[0] == '$')
		k_len = strlen(key);
	else
		k_len = strlen(key) + 1;
	s_len = strlen(str);
	if (start == 0)
		splits[0] = ft_strdup("");
	else
		splits[0] = ft_strdup_m(str, 0, start);
	splits[1] = ft_strdup(key_value);
	if (start + k_len < s_len)
		splits[2] = ft_strdup_m(str, start + k_len, s_len - (start + k_len));
	else
		splits[2] = ft_strdup("");
	if (!splits[0] || !splits[1] || !splits[2])
		return (free_splits(splits), NULL);
	return (splits);
}

char	*split_expansion(char *str, char *key, int start, char *key_value)
{
	char	**splits;
	char	*tmp;
	char	*result;

	splits = make_splits(str, key, start, key_value);
	if (!splits)
		return (NULL);
	tmp = ft_strjoin(splits[0], splits[1]);
	if (!tmp)
	{
		free_splits(splits);
		return (NULL);
	}
	result = ft_strjoin(tmp, splits[2]);
	free_splits(splits);
	free(tmp);
	tmp = NULL;
	free(str);
	if (!result)
		return (NULL);
	return (result);
}
