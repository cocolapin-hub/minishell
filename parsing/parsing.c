
#include "../minishell.h"


const char *redir_type_to_str(t_type type)
{
    if (type == REDIR_IN) return "redir.in";
    if (type == REDIR_OUT) return "redir.out";
    if (type == REDIR_APPEND) return "redir.append";
    if (type == REDIR_HEREDOC) return "redir.heredoc";
    if (type == PIPE) return "pipe";
    if (type == WORD) return "word";
    return "unknown";
}

void print_command(t_command *cmd, int index)
{
    int i;
    t_token *elem;

    if (!cmd)
    {
        printf("//cmd%d: NULL command pointer\n\n", index);
        return;
    }

    printf("//cmd%d:\n", index);

    // print args safely
    printf("//  args    = [");
    if (cmd->args)
    {
        for (i = 0; cmd->args[i]; i++)
        {
            printf("\"%s\"", cmd->args[i] ? cmd->args[i] : "(null)");
            if (cmd->args[i + 1])
                printf(", ");
        }
    }
    else
        printf("NULL");
    printf("]\n");

    // print redirection elements safely
    printf("//  element = ");
    if (!cmd->elem)
        printf("NULL\n");
    else
    {
        elem = cmd->elem;
        printf("[");
        while (elem)
        {
            printf("type: %s, value: %s",
                   redir_type_to_str(elem->type),
                   elem->value ? elem->value : "(null)");
            elem = elem->next;
            if (elem)
                printf(" | ");
        }
        printf("]\n");
    }

    // show environment placeholder
    printf("//  all     = all env\n");

    // show next command
    if (cmd->next)
        printf("//  next    = cmd%d\n", index + 1);
    else
        printf("//  next    = NULL\n");

    printf("\n");
}

void print_pipeline(t_command *cmd)
{
    int index = 1;

    while (cmd)
    {
        // debug pointers to catch invalid memory
        printf("DEBUG: cmd=%p next=%p args=%p elem=%p\n",
               (void*)cmd, (void*)cmd->next,
               (void*)cmd->args, (void*)cmd->elem);

        print_command(cmd, index);
        cmd = cmd->next;
        index++;
    }
}


void	parsing(char *line, t_shell *all, t_command **cmd)
{
	t_token 	*list = NULL;
	char		*cleaned_line;



	/*Etapes de mon parsing*/
	// if(line[0] == 59)

	cleaned_line = check_input(line, &all);
	// if(cleaned_line[0] == 59)



	if (!cleaned_line)
	{
		*cmd = NULL;
		return ;
	}

	/*Creation de la commande*/

	tokenisation(cleaned_line, &list, &all);
	if (!list)
	{
		*cmd = NULL;
		return ;
	}
	else
		error_handling(&all, &list);

	if (!list)
		*cmd = NULL;
	else
		set_command(cmd, list, all);


	//FREE EN COMMENTAIRE POUR L'INSTANT

	// if(!set_command(&cmd, list, all))
	// {
	// 	free(line);
	// 	free_tokens(list);
	// 	end_code(cmd);
	// }

	// /* ____PRINT CHECK____*/
	// while(list)
	// {
	// 	printf("**args: %u\ncmd: %s\n\n", list->type,  list->value);
	//  	list = list->next;
	// }

	// print_pipeline(*cmd);      // <-- to print result
	// if(list)
	// 	free_tokens(list);
	// free(cleaned_line);

//	return (cmd);
}