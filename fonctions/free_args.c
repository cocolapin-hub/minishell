/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:08:32 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/17 15:08:53 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_args(char **args)
{
	int	x;

	x = 0;

	if (!args)
		return;

	while (args[x])
		free(args[x++]);

	free(args);
}
