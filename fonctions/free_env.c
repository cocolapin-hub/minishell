/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:04:27 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/17 15:09:50 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_SHELL *all)
{
	t_local *tmp1;
	t_local	*tmp2;

	if(!all)
		return;

	/*free chaque maillon env*/
	tmp1 = all->env;
	while(tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1->key);
		free(tmp1->value);
		free(tmp1);
		tmp1 = tmp2;
	}

	/*free la struct*/
	free(all);
}