#include "../../../minishell.h"


int		handle_number_zero(char **str, int x)
{
// 	//return bash + toutes lettres d'apres
	int len;

	len = ft_strlen("minishell");
	*str = split_for_expansion(*str, "$0", x, "minishell"); //split_for_expansion(*str, "$$", x, "");

	return (x + len);
}