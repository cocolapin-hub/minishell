#include "../minishell.h"

int	builtin_exit(char **args)
{
	(void)args;				// par d'arg à traiter
	write(1, "exit\n", 5);	// affiche exit comme bash
	exit(0);				// quitte shell avec code 0 (succes)
}
