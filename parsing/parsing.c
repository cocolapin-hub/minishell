
#include "../minishell.h"

#include <stdio.h>

// const char *redir_type_to_str(t_type type)
// {
//     if (type == REDIR_IN) return "redir.in";
//     if (type == REDIR_OUT) return "redir.out";
//     if (type == REDIR_APPEND) return "redir.append";
//     if (type == REDIR_HEREDOC) return "redir.heredoc";
//     if (type == PIPE) return "pipe";
//     if (type == WORD) return "word";
//     return "unknown";
// }

// void    print_command(t_command *cmd, int index)
// {
//     int     i;
//     t_token *elem;

//     printf("//cmd%d:\n", index);

//     // print args
//     printf("//  args    = [");
//     if (cmd->args)
//     {
//         for (i = 0; cmd->args[i]; i++)
//         {
//             printf("\"%s\"", cmd->args[i]);
//             if (cmd->args[i + 1])
//                 printf(", ");
//         }
//     }
//     printf(", NULL]\n");

//     // print elements (redirs)
//     printf("//  element = ");
//     if (!cmd->elem)
//         printf("NULL\n");
//     else
//     {
//         elem = cmd->elem;
//         printf("[");
//         while (elem)
//         {
//             printf("type: %s, value: %s", redir_type_to_str(elem->type), elem->value);
//             if (elem->next)
//                 printf(", next: ");
//             elem = elem->next;
//         }
//         printf("]\n");
//     }

//     // show env placeholder
//     printf("//  all     = all env\n");

//     // show next
//     if (cmd->next)
//         printf("//  next    = cmd%d\n", index + 1);
//     else
//         printf("//  next    = NULL\n");

//     printf("\n");
// }

// void    print_pipeline(t_command *cmd)
// {
//     int index = 1;

//     while (cmd)
//     {
//         print_command(cmd, index);
//         cmd = cmd->next;
//         index++;
//     }
// }


t_command	*parsing(char *line, t_shell *all)
{
	t_token 	*list = NULL;
	t_command 	*cmd = NULL;
	char		*cleaned_line;

	/*ligne vide*/
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		end_code(cmd);
	}

	/*Etapes de mon parsing*/
	cleaned_line = check_input(line);

	if (!cleaned_line)
		return NULL;

	tokenisation(cleaned_line, &list, &all);
	error_handling(&all, &list);
	set_command(&cmd, list, all);


	//FREE EN COMMENTAIRE POUR L'INSTANT

	// if(!set_command(&cmd, list, all))
	// {
	// 	free(line);
	// 	free_tokens(list);
	// 	end_code(cmd);
	// }

	/* ____PRINT CHECK____*/
	// while(list)
	// {
	// 	printf("**args: %s\ncmd: %s\n\n", list->type,  list->value);
	//  	list = list->next;
	// }

	print_pipeline(cmd);      // <-- to print result

	// if(list)
	// 	free_tokens(list);
	// free(cleaned_line);

	return (cmd);
}