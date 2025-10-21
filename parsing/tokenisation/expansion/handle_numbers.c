
#include "../../../minishell.h"


int		handle_numbers(char **str, int x)
{
	//il faut return rien ou toutes les lettres d'apres
	*str = split_for_expansion(*str, "$1", x, "");

	return (x);
}
