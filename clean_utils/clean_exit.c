
#include "../minishell.h"

void	clean_exit(t_shell *all, t_command *cmd_list, int code)
{
	(void)all;
	(void)cmd_list;

	if (all)
		free_env(all);

	if (cmd_list)
		free_command(cmd_list);

	clear_history();
	exit(code);
}
