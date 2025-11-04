/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:46:18 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(const char *s, char c)
{
	int	is_word;
	int	word_count;

	word_count = 0;
	is_word = 0;
	while (1)
	{
		if (*s != c && !is_word)
			is_word = 1;
		else if ((*s == c || !*s) && is_word)
		{
			is_word = 0;
			word_count++;
		}
		if (!*s)
			break ;
		s++;
	}
	return (word_count);
}

char	**free_str_arr(char **arr, int nelm)
{
	int	x;

	x = -1;
	while (++x < nelm)
		free(arr[x]);
	free(arr);
	arr = NULL;
	return (NULL);
}

char	**copy_words(const char *s, char c, char **res, int max)
{
	int		is_word;
	int		word_count;
	char	*beg;

	word_count = 0;
	is_word = 0;
	while (word_count < max)
	{
		if (*s != c && !is_word)
		{
			is_word = 1;
			beg = (char *)s;
		}
		else if ((*s == c || !*s) && is_word)
		{
			is_word = 0;
			res[word_count] = ft_calloc(s - beg + 1, 1);
			if (!res[word_count])
				return (free_str_arr(res, max));
			ft_strlcpy(res[word_count++], beg, s - beg + 1);
		}
		s++;
	}
	res[word_count] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		max;
	char	**res;

	if (!s)
		return (NULL);
	max = count_words(s, c);
	res = ft_calloc(max + 1, sizeof(char *));
	if (!res)
		return (NULL);
	return (copy_words(s, c, res, max));
}
/*
#include <stdio.h>

int	main(void)
{
	char str[] = "lorevarius a, semper congue, euismod non, mi.";
	char charset = 'i';
	char **result;
	int	x;

	x = 0;
	result = ft_split(str, charset);
	while (result[x])
	{
		printf("%s\n", result[x]);
		free(result[x]);
		x++;
	}
	free(result);
}*/
