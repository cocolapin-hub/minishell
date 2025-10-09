
#include "../minishell.h"

//proteger les malloc et autre et ajouter les free

void		create_args(t_token *list, int token_count, int skip_next, char ***args)
{
	t_token	*tmp;

	tmp = list;

	/*count len with a tmp == all words but the one right after a redir*/
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			skip_next = 1;

		else if (tmp->type == WORD)
		{
			if (skip_next)
				skip_next = 0;
			else
				token_count++;
		}
		tmp = tmp->next;
	}

	*args = ft_calloc(token_count + 1, sizeof(char *));
	if (!(*args))
		*args = NULL;
	else
		(*args)[token_count] = 0;
}

void		create_cmd(t_token **tmp, t_token **new, t_token **start, t_token **end)
{

    // Only take a WORD that is NOT an option (-*) as the redirection target
    t_token *target = (*tmp)->next;
    while (target && target->type == WORD && target->value[0] == '-')
        target = target->next;  // skip option-like words

    if (target && target->type == WORD)
    {
        *new = malloc(sizeof(t_token));
        (*new)->type = (*tmp)->type;
        (*new)->value = ft_strdup(target->value);
        (*new)->next = NULL;

        if (!(*start))
            *start = *new;
        else
            (*end)->next = *new;
        *end = *new;

        *tmp = target; // consume only the actual filename
    }
}

void		fill_args(t_token *list, char ***args)
{
	int		skip_next;
//	int 	token_count;
	int		x;

	/*creates args */
	create_args(list, 0, 0, args);

	/*allocate value*/
    skip_next = 0;
    x = 0;
	while (*args && list && list->type != PIPE)
    {
        if (list->type == REDIR_IN || list->type == REDIR_OUT
            || list->type == REDIR_APPEND || list->type == REDIR_HEREDOC)
            skip_next = 1;
        else if (list->type == WORD)
        {
			if (skip_next == 1 && ft_strcmp(list->value, "-n"))
				skip_next = 0;
            else
                (*args)[x++] = ft_strdup(list->value);
				//protection needed here
        }
        list = list->next;
    }
}

void		fill_elements(t_token **list, t_token **elements)
{
	t_token	*tmp = *list;
	t_token	*start = NULL;
	t_token	*end = NULL;
	t_token	*new = NULL;

	tmp = *list;
	if (!(*list) || !list)
	{
		*elements = NULL;
		return ;
	}

	/*fill element struct*/
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			create_cmd(&tmp, &new, &start, &end);
		tmp = tmp->next;
	}
	*elements = start;

	/*move after the pipe for next cmd*/
	if (tmp && tmp->type == PIPE)
		*list = tmp->next;
	else
		*list = tmp;
}


t_command	*set_command(t_command **cmd, t_token *list, t_shell *all)
{
	t_command	*new;
	t_token		*elements;
	char 		**args;

	while (list)
    {
    	args = NULL;
        fill_args(list, &args);
        if (!args)
        {
            list = list->next;
            continue;
        }

        fill_elements(&list, &elements);

        new = ft_lstnew_cmd(args, elements, all);
        if (!new)
            return NULL;

        if (!*cmd)
            *cmd = new;
        else
            ft_lstadd_back_cmd(cmd, new);
    }
	//free_args(args); not here perhaps
	return (*cmd);
}





// EXEMPLE:	cat -n < in.txt | grep hello > out.txt

//cmd1:
//  args    = ["cat", "-n", NULL]
//  element = [type: redir.in, value: in.text, next: null]
//  all	 	= all env
//  next    = cmd2


//cmd1:
//  args    = ["cat", "-n", NULL]
//  element = [type: redir.out, value: out.text, next: null]
//  all	 	= all env
//  next    = cmd2