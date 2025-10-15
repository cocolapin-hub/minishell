
#include "../minishell.h"


//echo $lol -> apres un -export lol (donc lol est vide)  --> comment il gere le =
//eho d'expansion qui n existe pas
//expansion qui n'existe pas


int handles_command(char *line, int x, t_token **list, t_shell **all)
{
    t_token 	*new;
    char 		*cmd;
    char 		*tmp;
    char 		quote;
    int 		y;
    int 		was_in_quotes;
    char 		**split;
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
            tmp = between_quotes(line, &quote, &x, all);
            was_in_quotes = 1;  // Mark that this token had quotes
            y = x;
        }
        else
            tmp = outside_quotes(line, &x, &y, all);

        if (!tmp)
        {
            free(cmd);
            return (-1);
        }
        cmd = ft_strjoin(cmd, tmp);
        free(tmp);
    }

	if (ft_strcmp(cmd, "."))
	{
		write(2, ".: command not found\n", 21);
        (*all)->last_status = 127;
        free(cmd);
        return (-1);
	}
    if (ft_strcmp(cmd, "") == 0 && !*list && (line[x - 1] == 39 || line[x - 1] == 34))
    {
        if (line[x - 1] == 39)
            write(2, "\'\': command not found\n", 22);
        else
            write(2, "\"\": command not found\n", 22);
        (*all)->last_status = 127;
        free(cmd);
        return (-1);
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
                new = ft_lstnew_token(split[i]);
                new->type = WORD;
                new->amount = Q_NONE;

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
        new = ft_lstnew_token(cmd);
        new->type = WORD;
        new->amount = quote;

        if (!*list)
            *list = new;
        else
            ft_lstadd_back(list, new);

        // Don't free cmd - token owns it
    }
    return (x);
}

int		handles_special_char(char *line, int x, t_token **list)
{
	t_token	*new;
	char	*cmd = NULL;
	int		y;

	y = x;

	/*saves the pipe*/
	if (line[x] == 124)
		cmd = ft_strdup_m(line, x, 1);

	/*saves arrows*/
	else if (line[x] == 60 || line[x] == 62)
	{
		if (line[x + 1] == line[x])
		{
			cmd = ft_strdup_m(line, x, 2);
			y++;
		}
		else
			cmd = ft_strdup_m(line, x, 1);
	}

	/*creats the 1st list element*/
	new = ft_lstnew_token(cmd);
	if (!*list)
		*list = new;

	/*creats others list element*/
	else
		ft_lstadd_back(list, new);

	return (y + 1);
}

t_token	*tokenisation(char *line, t_token **list, t_shell **all)
{
	int	x;

	x = 0;
	while (line[x])
	{
		while (line[x] == 32 || line[x] == 9)
			x++;
		if (line[x] == '|' || line[x] == '<' || line[x] == '>')
			x = handles_special_char(line, x, list);
		else
		{
			x = handles_command(line, x, list, all);
			if ((*all)->last_status == 258 || x == -1)
			{
				free_tokens(*list);
				printf("%d %d\n",(*all)->last_status, x);
				return (NULL);
			}
		}
	}
	return (*list);
}