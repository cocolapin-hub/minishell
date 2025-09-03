

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) // ctrl-D
            break;
        if (*line)
            add_history(line);
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }
        printf("You typed: %s\n", line);
        free(line);
    }
    return 0;
}



/*
 readline → pour lire la ligne.
 find_in_path → pour trouver la commande.
 exec_command → pour exécuter.
*/













