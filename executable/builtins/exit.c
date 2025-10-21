#include "../../minishell.h"

int builtin_exit(char **args, t_shell *all, t_command *cmd_list)
{
	long long 	val;

	val = 0;
	if (cmd_list->next == NULL && cmd_list == all->cmd_head)
		write(2, "exit\n", 5);

	// aucun argument
	if (!args[1])
		exit_clean_af(all, cmd_list, all->last_status);

	// non numérique
	else if (!ft_islonglong(args[1], &val) || !ft_strisnum(args[1]))
	{
		write(2, "hello\n: ", 6);
		write(2, "exit: ", 6);
		print_error_exec(args[1], "numeric argument required");
		exit_clean_af(all, cmd_list, 2);
	}

	// trop d'arguments
	else if (args[2])
	{
		print_error_exec("exit", "too many arguments");
		return (1);				// NE PAS quitter
	}

	//cas normal
	ft_islonglong(args[1], &val);
	exit_clean_af(all, cmd_list, val % 256);
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