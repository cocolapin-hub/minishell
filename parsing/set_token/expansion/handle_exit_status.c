#include "../../../minishell.h"


int 	handle_exit_status(char **str, int last_status, int x)
{
    char *status;
	int len;

	status = ft_itoa(last_status);
    *str = split_for_expansion(*str, "$?", x, status);
    len = ft_strlen(status);
    free(status);
    return (x + len);
}
