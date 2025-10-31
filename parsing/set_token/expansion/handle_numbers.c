
#include "../../../minishell.h"

int	handle_numbers(char **str, int x)
{
	*str = split_expansion(*str, "$1", x, "");
	return (x);
}
