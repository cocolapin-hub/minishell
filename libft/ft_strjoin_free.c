/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/05 18:14:50 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;
    if (!s1 || !s2)
        return (NULL);
    result = ft_strjoin(s1, s2);
    free(s1);
    if (s2 != skip())
        free(s2);
    return (result);
}

