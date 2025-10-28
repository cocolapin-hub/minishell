
#include "../../minishell.h"

// void	fatal_error(const char *msg, int code)	// cas où le shell  ne peut pas continuer (pipe, fork, dup2 echoue)
// {
// 	perror(msg);
// 	exit(code);
// }



// void	print_error_exec(char *cmd, char *msg)	// cas où commande inconnue / execve fail mais shell continue (bash ne quitte pas sur un ls raté par ex)
// {
// 	write(2, cmd, ft_strlen(cmd));
// 	write(2, ": ", 2);
// 	write(2, msg, ft_strlen(msg));
// 	write(2, "\n", 1);
// }

// int	exec_error(const char *cmd, const char *msg, int code)
// {
// 	write(2, "minishell: ", 11);
// 	if (cmd && *cmd)
// 	{
// 		write(2, cmd, ft_strlen(cmd));
// 		write(2, ": ", 2);
// 	}
// 	write(2, msg, ft_strlen(msg));
// 	write(2, "\n", 1);
// 	return (code);
// }

int	redir_error(char *file, char *msg)
{
	print_err("redir", file, msg);
	return (1);
}
void	print_invalid_id(char *arg, t_shell *all)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	all->last_status = 1;
}

void	fatal_exit(const char *msg, int code)
{
	perror(msg);
	exit(code);
}

void	exit_clean_af(t_shell *all, t_command *cmd_list, int code)
{
	(void)all;
	(void)cmd_list;

	// if (cmd_list)
	// 	free_command(cmd_list);
	// if (all->env)
	// 	free_env(all);
	clear_history();
	exit(code);
}

// void clean_and_exit(t_shell *all, int status)
// {
// 	free_env(all->env);
// 	free_history();
// 	// si necessário: free cmd list
// 	exit(status);
// }

/*

minishell: cmd: msg	print_err(cmd, NULL, msg)
minishell: cmd: arg: msg	print_err(cmd, arg, msg)
minishell: msg	print_err(NULL, NULL, msg)

*/