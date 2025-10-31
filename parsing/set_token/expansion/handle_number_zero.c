#include "../../../minishell.h"


int	handle_number_zero(char **str, int x)
{
	int	len;

	len = ft_strlen("minishell");
	*str = split_expansion(*str, "$0", x, "minishell");
	return (x + len);
}
