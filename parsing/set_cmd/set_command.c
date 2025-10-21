
#include "../../minishell.h"


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
		{
            *cmd = new;
			all->cmd_head = *cmd;
		}
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