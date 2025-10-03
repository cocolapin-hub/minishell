
#include "../../minishell.h"

void	free_command(t_command *cmd)
{
	t_command	*tmp;
	t_token		*tok;
	t_token		*next_tok;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_split(cmd->args);
		tok = cmd->elem;
		while (tok)
		{
			next_tok = tok->next;
			free(tok->value);
			free(tok);
			tok = next_tok;
		}
		free(cmd);
		cmd = tmp;
	}
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}