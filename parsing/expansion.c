/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/05 18:00:50 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 3. Expansion et quote removal sur t_token
//    - Parcourir chaque token de type WORD
//    - Si quote != Q_SINGLE : remplacer les variables d’environnement ($VAR, $?) par leur valeur

	// sauvegarde des var

	//remplacer les words par leur reel valeur si necessaire
	//remplacer $? par valeur de sortie (0 / 1)




void		expansion(t_local *env, t_token **list)
{
	/*this handles when we need to do expansions*/
	t_token *lst2 = *list;
	t_local *env2;
	char 	*value;

	while(lst2)
	{
		env2 = env;
		if (lst2->value[0] == '$')
		{
			value = ft_strdup(lst2->value, 1, ft_strlen(lst2->value) - 1);
			while(env2)
			{
				if (strcmp(value, env2->key) == 0 && lst2->amount != Q_SINGLE)
				{
					(lst2)->value = env2->value;
					break;
				}
				env2 = env2->next;
			}
		}
		lst2 = (lst2)->next;
	}

	/*second part handles $?, i will do it later by myself*/

}