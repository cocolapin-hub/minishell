
#include "../../minishell.h"

void	fatal_error(const char *msg, int code)	// cas où le shell  ne peut pas continuer (pipe, fork, dup2 echoue)
{
	perror(msg);
	exit(code);
}

void	exit_clean_af(t_shell *all, t_command *cmd_list, int code)
{
	if (cmd_list)
		free_command(cmd_list);
	if (all->env)
		free_env(all);
	//clear_history(); 	??
	exit(code);
}

void	print_error_exec(char *cmd, char *msg)	// cas où commande inconnue / execve fail mais shell continue (bash ne quitte pas sur un ls raté par ex)
{
	//write(2, "minishell: ", 11); zsh ??
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

int	redir_error(char *file, char *msg)
{
	write(2, "minishell: ", 11);
	if (file && *file)
	{
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

int	exec_error(const char *cmd, const char *msg, int code)
{
	write(2, "minishell: ", 11);
	if (cmd && *cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (code);
}

void	print_invalid_identifier(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
