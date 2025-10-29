#include "../minishell.h"

void	handles_ctrl_d(char *line, t_shell all, t_command *cmd_list)
{
	if (!line)
	{
		// Ctrl-D pressed
		write(2, "exit\n", 5);
		clean_exit(&all, cmd_list, all.last_status);
	}
	return ;
}