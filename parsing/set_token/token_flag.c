#include "../../minishell.h"

void	token_flag_off(char *cmd, int quote, t_token **list)
{
	char	**split;
	t_token	*new;
	int		i;

	i = 0;
	split = ft_split(cmd, ' ');
	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) > 0)
		{
			new = ft_lstnew_token(split[i], quote);
			if (!*list)
				*list = new;
			else
				ft_lstadd_back(list, new);
		}
		i++;
	}
	free(cmd);
}

void	token_flag_on(char *cmd, int quote, t_token **list)
{
	t_token	*new;

	new = ft_lstnew_token(cmd, quote);
	if (!*list)
		*list = new;
	else
		ft_lstadd_back(list, new);
}