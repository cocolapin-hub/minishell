
#include "../minishell.h"


int ft_count_strings(char **arr)
{
    int i = 0;

    while (arr[i])
        i++;
    return i;
}