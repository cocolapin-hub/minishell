
#include "../../minishell.h"

static void	free_split_and_cmd(char **split, char *cmd)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
	free(cmd);
}

void	token_flag_off(char *cmd, int quote, t_token **list)
{
	char	**split;
	t_token	*new;
	int		i;

	split = ft_split(cmd, ' ');
	if (!split)
	{
		free(cmd);
		return ;
	}
	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) > 0)
		{
			new = ft_lstnew_token(split[i], quote);
			if (!new)
			{
				free_split_and_cmd(split, cmd);
				return ;
			}
			if (!*list)
				*list = new;
			else
				ft_lstadd_back(list, new);
		}
		i++;
	}
	free_split_and_cmd(split, cmd);
}

void	token_flag_on(char *cmd, int quote, t_token **list)
{
	t_token	*new;

	new = ft_lstnew_token(cmd, quote);
	if (!new)
	{
		free(cmd);
		return ;
	}
	if (!*list)
		*list = new;
	else
		ft_lstadd_back(list, new);
}
