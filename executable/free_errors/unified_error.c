
#include "../../minishell.h"

void	print_err(const char *cmd, const char *arg, const char *msg)
{
	write(2, "minishell: ", 11);
	if (cmd && *cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg && *arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

int	error_code(const char *cmd, const char *msg, int code)
{
	print_err(cmd, NULL, msg);
	return (code);
}
