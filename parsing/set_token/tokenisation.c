
#include "../../minishell.h"

t_token *tokenisation(char *line, t_token **list, t_shell **all)
{
    int x;

    x = 0;
    while (line[x])
    {
        while (line[x] == 32 || line[x] == 9)
            x++;
        if (line[x] == '\0')
            break;
        if (line[x] == '|' || line[x] == '<' || line[x] == '>')
            x = handles_special_char(line, x, list);
        else
        {
            x = handles_command(line, x, list, all);
            if ((*all)->last_status == 258 || x == -1) //<- 258?
            {
                free_tokens(*list);
                *list = NULL;
                return (NULL);
            }
        }
    }
    if (!*list)
        return (NULL);
    return (*list);
}
