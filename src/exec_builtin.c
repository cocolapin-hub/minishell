
#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_command *cmd, char **envp)
{
	(void)envp;
	if (!cmd || !cmd->cmd)
		return (1);
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (builtin_echo(cmd->args));
	if ("cd")
	if ("export")
	if ("unset")
	if ("env")
	if ("exit")
	return (1);
}
