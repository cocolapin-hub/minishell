
#include "../../minishell.h"

int	builtin_exit(char **args, t_shell *all, t_command *cmd_list)
{
	long long	val;
	char		*trimmed;

	trimmed = ft_strtrim(args[1], " \t\n");
	val = 0;
	if (cmd_list->next == NULL && cmd_list == all->cmd_head)
		write(2, "exit\n", 5);
	if (!args[1])
		clean_exit(all, cmd_list, all->last_status);
	else if (!ft_islonglong(trimmed, &val) || !ft_strisnum(trimmed))
	{
		write(2, "exit: ", 6);
		print_err("exit", args[1], "numeric argument required");
		free(trimmed);
		clean_exit(all, cmd_list, 2);
	}
	else if (args[2])
	{
		free(trimmed);
		print_err("exit", NULL, "too many arguments");
		all->last_status = 1;
		return (1);
	}
	ft_islonglong(trimmed, &val);
	return (free(trimmed), clean_exit(all, cmd_list, val % 256), 0);
}
