
#include "../../../minishell.h"


char 	*clean_after_expansion(char *str)
{
	char 	*new_line;
	int		len;
	int 	x;
	int 	y;

	len = ft_strlen(str);
	new_line = malloc(sizeof(char) * len + 1);
	if (!new_line)
		return (NULL);

	y = 0;
	x = 0;
	while(str[x])
	{
		/*handles double spacing and tab*/
		if ((x != 0 && str[x] == 32 && str[x - 1] == 32)
		|| (x != 0 && str[x] == 9 && str[x - 1] == 9))
			x++;

		/*normal copy*/
		else
			new_line[y++] = str[x++];
	}

	new_line[y] = '\0';
	return (new_line);
}
