#include "../minishell.h"

void	free_command(t_command *cmd_list)
{
	t_command	*tmp;

	while(cmd_list)
	{
		tmp = cmd_list->next;

		if (cmd_list->args)
			free_args(cmd_list->args);

		if (cmd_list->elem)
			free_tokens(cmd_list->elem);

		free(cmd_list);
		cmd_list = tmp;
	}
}
