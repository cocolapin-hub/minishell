#include "../minishell.h"

int handles_ctrl_c(t_shell all, char *line)
{
	int tmp_fd;

	if (g_in_heredoc == SIGINT)
	{
		g_in_heredoc = 0;  		// Reset le flag
		all.last_status = 130;  // exit status pour SIGINT
		free(line);

		//reinitialise le STDIN
		tmp_fd = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(tmp_fd, STDIN_FILENO);
		close(tmp_fd);
		return (1);
	}
	return (0);
}