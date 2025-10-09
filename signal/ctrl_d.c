#include "../minishell.h"

void	handles_ctrl_d(char *line, t_shell all, t_command *cmd_list)
{
	if (!line)
	{
		// Ctrl-D pressed
		printf("exit\n");
		exit_clean_af(&all, cmd_list, all.last_status);
	}
	return ;
}