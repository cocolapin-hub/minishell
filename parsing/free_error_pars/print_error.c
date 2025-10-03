#include "../../minishell.h"

void		print_error(char *line, char *msg)
{
	write(2, &line, strlen(line));
	write(2, ":", 1);
	write(2, &msg, strlen(msg));
	write(2, "\n", 1);
}