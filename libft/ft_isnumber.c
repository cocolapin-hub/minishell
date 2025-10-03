


#include "../minishell.h"

int ft_isnumber(const char *str)
{
    int i;

    if (!str || !*str)
        return (0);
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}
