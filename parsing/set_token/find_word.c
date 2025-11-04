/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/04 11:53:27 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_word(int *y, int x, char *line, char **tmp)
{
	int	start;

	start = *y;
	while (line[*y] && line[*y] != 34 && line[*y] != 39 && line[*y] != 32
		&& line[*y] != 9 && line[*y] != 60 && line[*y] != 62
		&& line[*y] != 124)
		(*y)++;
	*tmp = ft_strdup_m(line, x, *y - x);
	return (start);
}
