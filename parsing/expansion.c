/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/12 14:40:11 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 3. Expansion et quote removal sur t_token
//    - Parcourir chaque token de type WORD
//    - Si quote != Q_SINGLE : remplacer les variables d’environnement ($VAR, $?) par leur valeur

	// sauvegarde des var

	//remplacer les words par leur reel valeur si necessaire
	//remplacer $? par valeur de sortie (0 / 1)

char		*expansion(t_local *env, int last_status, char *str, char quote)
{
	/*this handles when we need to do expansions*/
	t_local *env2;
	char 	*value;


	env2 = env;

	/*Handles $?*/
	if (strcmp(str, "$?") == 0 && quote != 39)
	{
		free(str);
		str = ft_itoa(last_status);
	}

	/*Handle $VAR*/
	else if (str[0] == '$' && quote != 39)
	{
		value = ft_strdup_m(str, 1, ft_strlen(str) - 1);
		while(env2)
		{
			if (strcmp(value, env2->key) == 0 )
			{
				free(str);
				str = ft_strdup_m(env2->value, 0, ft_strlen(env2->value));
				break;
			}
			env2 = env2->next;
		}
		free(value);
	}
	return (str);

}