
#include "../minishell.h"

int		redir_error(char *file, char *msg)
{
	print_err(NULL, file, msg);
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
