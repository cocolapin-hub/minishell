#include "../minishell.h"


int	ft_islonglong(const char *str, long long *out)
{
    long long 	val;
	int			is_long;

	is_long = 1;
	val = ft_strtoll(str, &is_long);

    if (is_long == 0)
		return 0;

    if (out)
    	*out = val;

    return (1);
}