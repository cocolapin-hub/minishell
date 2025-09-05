/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:39:27 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/05 16:48:57 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_env(t_local **env, char *tab, char *value, char *key)
{
	t_local *last;
	t_local	*new;
	int		len;
	int		y;

	len = ft_strlen(tab);
	y = 0;
	while(tab[y] && tab[y] != 61)
		y++;

	/*save key & value*/
	if (tab[y] == 0)
	{
		key = ft_strdup(tab, 0, y);
		value = NULL;
	}
	else
	{
		key = ft_strdup(tab, 0, y);
		y++;
		value = ft_strdup(tab, y, len - y);
	}

	/*send to env*/
	new = ft_lstnew_env(value, key);
	if (!*env)
		*env = new;
	else
	{
		last = *env;
    	while (last->next)
        	last = last->next;
    	last->next = new;
	}
}

void	setup_env(t_local **env, char **envp)
{
	char	*value = NULL;
	char	*key = NULL;
	int 	x;

	x = 0;
	while (envp[x])
	{
		fill_env(env, envp[x], value, key);
		x++;
	}
}