/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:08:15 by claffut           #+#    #+#             */
/*   Updated: 2025/04/22 20:25:01 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = 0;
	while (*s)
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)last);
}
/*
#include <string.h>
#include <stdio.h>

int main(void) 
{
    const char *str = "Coucou les biChes!";
    int	c = 'C';

	char	*result = ft_strrchr(str, c);

	if (result)
		printf("Dernier '%c' trouvé à la position : %ld\n", c, result - str);
	else
		printf("'%c' non trouvé.\n", c);

    return 0;
}
*/