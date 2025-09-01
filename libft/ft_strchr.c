/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:49:34 by claffut           #+#    #+#             */
/*   Updated: 2025/04/22 20:22:56 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
/*
#include <string.h>
#include <stdio.h>

int main(void) 
{
    const char *str = "Coucou les biches!";
    int	c = 'C';

	char	*result = ft_strchr(str, c);

	if (result)
		printf("Premier '%c' trouvé à la position : %ld\n", c, result - str);
	else
		printf("Caractere '%c' non trouvé.\n", c);

    return 0;
}
*/