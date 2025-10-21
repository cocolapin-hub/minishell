
#include "../../minishell.h"


int handles_command(char *line, int x, t_token **list, t_shell **all)
{
	int 		was_in_quotes;
	char 		**split;
	char 		quote;
    t_token 	*new;
    char 		*cmd;
    char 		*tmp;
    int 		y;
    int 		i;


    cmd = ft_strdup("");
    quote = 0;
    was_in_quotes = 0;
    y = x;

    while (line[x])
    {
        if (line[x] == 32 || line[x] == 9 || line[x] == 124 ||
            line[x] == 60 || line[x] == 62)
            break;

        if (line[x] == 39 || line[x] == 34)
        {
            tmp = between_quotes(line, &quote, &x, all, list);
            was_in_quotes = 1;  // Mark that this token had quotes
            y = x;
        }
        else
            tmp = outside_quotes(line, &x, &y, all, list);

        if (!tmp)
        {
            free(cmd);
            return (-1);
        }
        cmd = ft_strjoin(cmd, tmp);
        free(tmp);
    }

    // If NOT in quotes and contains spaces, split it
    if (!was_in_quotes && ft_strchr(cmd, ' '))
    {
        split = ft_split(cmd, ' ');
        i = 0;
        while (split[i])
        {
            if (ft_strlen(split[i]) > 0)
            {
                new = ft_lstnew_token(split[i], quote);
                // new->type = WORD;
                // new->amount = Q_NONE;

                if (!*list)
                    *list = new;
                else
                    ft_lstadd_back(list, new);
            }
            i++;
        }
        free(cmd);
        // Don't free split array or split[i] - tokens own them now
    }
    else
    {
        // Keep as one token (was in quotes or no spaces)
        new = ft_lstnew_token(cmd, quote);
        // new->type = WORD;
        // new->amount = quote;

        if (!*list)
            *list = new;
        else
            ft_lstadd_back(list, new);

        // Don't free cmd - token owns it
    }
    return (x);
}

