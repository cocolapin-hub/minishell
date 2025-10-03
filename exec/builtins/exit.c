#include "../../minishell.h"

int builtin_exit(char **args, t_SHELL *all, t_command *cmd_list)
{
	long code;

	write(1, "exit\n", 5);
	if (!args[1])				// aucun argument
		exit_clean_af(all, cmd_list, all->last_status);
	if (!ft_isnumber(args[1]))	// non numérique
	{
		print_error("exit", "numeric argument required");
		exit_clean_af(all, cmd_list, 2);
	}
	if (args[2])				// trop d'arguments
	{
		print_error("exit", "too many arguments");
		return (1);				// NE PAS quitter
	}
	code = ft_atol(args[1]);	// conversion en long
	exit_clean_af(all, cmd_list, (unsigned char)code);
	return (0);
}

/*

numeric error → 2

too many args → 1

Toujours afficher "exit" avant de quitter.

Troncature : exit 260 → code = 260 % 256 = 4. ????????

		La troncature modulo 256
			Le code de sortie d’un processus est limité à un octet (0 → 255).
			En C, waitpid ne garde que 8 bits pour le code de sortie.
		Donc :
			exit 42 → 42
			exit -1 → 255 (car -1 % 256 = 255)
			exit 260 → 4 (car 260 % 256 = 4)
			exit 9999 → 15 (car 9999 % 256 = 15)
		C’est ce qu’on appelle la troncature.
		En pratique, ça se fait en castant en unsigned char

*/