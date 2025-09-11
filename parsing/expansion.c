/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/10 14:19:55 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 3. Expansion et quote removal sur t_token
//    - Parcourir chaque token de type WORD
//    - Si quote != Q_SINGLE : remplacer les variables d’environnement ($VAR, $?) par leur valeur

	// sauvegarde des var

	//remplacer les words par leur reel valeur si necessaire
	//remplacer $? par valeur de sortie (0 / 1)

void		expansion(t_local *env, int last_status, t_token **list)
{
	/*this handles when we need to do expansions*/
	t_token *lst2 	= *list;
	t_local *env2;
	char 	*value;

	while(lst2)
	{
		env2 = env;

		/*Handles $?*/
		if (strcmp(lst2->value, "$?") == 0 && lst2->amount != Q_SINGLE)
		{
			free(lst2->value);
			lst2->value = ft_itoa(last_status);
		}

		/*Handle $VAR*/
		else if (lst2->value[0] == '$' && lst2->amount != Q_SINGLE)
		{
			value = ft_strdup(lst2->value, 1, ft_strlen(lst2->value) - 1);
			while(env2)
			{
				if (strcmp(value, env2->key) == 0 )
				{
					free(lst2->value);
					lst2->value = ft_strdup(env2->value, 0, ft_strlen(env2->value));
					break;
				}
				env2 = env2->next;
			}
			free(value);
		}
		lst2 = (lst2)->next;
	}
}