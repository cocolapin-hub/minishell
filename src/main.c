
#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static char	**split_input(char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**args;
	t_command	cmd;

	(void)argc;
	(void)argv;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line) // ctrl-D
			break;
		if (*line)
			add_history(line);
		args = split_input(line);
		if (!args)
		{
			free(line);
			continue;
		}
		cmd.cmd = args[0];
		cmd.args = args;
		cmd.next = NULL;
		if (ft_strncmp(cmd.cmd, "exit", 4) == 0)
		{
			free_split(args);
			free(line);
			break;
		}
		run_command(&cmd, envp);
		free_split(args);
		free(line);
	}
	return (0);
}






// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// int main(void)
// {
//     char *line;

//     while (1)
//     {
//         line = readline("minishell$ ");
//         if (!line) // ctrl-D
//             break;
//         if (*line)
//             add_history(line);
//         if (strcmp(line, "exit") == 0)
//         {
//             free(line);
//             break;
//         }
//         printf("You typed: %s\n", line);

//         free(line);
//     }
//     return 0;
// }



/*
 readline → pour lire la ligne.
 find_in_path → pour trouver la commande.
 exec_command → pour exécuter.
*/













