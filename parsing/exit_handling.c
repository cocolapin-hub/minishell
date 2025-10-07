
#include "../minishell.h"

void	simple_exit(char **exit_line, char *line, int len)
{
	if (exit_line[1] == 0 || (ft_isnumber(exit_line[1]) && len == 2))
		{
			free(line);
			write(1, "exit\n", 5);
			exit (1);
			//end_code(cmd);
		}
}

void	unvalid_exit(char **exit_line, char *line)
{
	if (!ft_isnumber(exit_line[1]))
	{
		free(line);
		write(1, "exit\n", 5);
		write(1, "exit: ", 6);
		write(1, exit_line[1], ft_strlen(exit_line[1]));
		write(1, ": numeric argument required\n", 28);
		exit (1);
		//end_code(cmd);
	}
}
char	*exit_handling(char *line)
{
	char	**exit_line;
	int		len;

	exit_line = ft_split(line, ' ');
	len = ft_count_strings(exit_line);

	if (ft_strcmp(exit_line[0], "exit") == 0)
	{
		simple_exit(exit_line, line, len);
		unvalid_exit(exit_line, line);

		//too many arguments apres exit (wont end code)
		if (len > 2)
		{
			free(line);
			write(1, "exit\n", 5);
			write(1, "exit: too many arguments\n", 25);
			return (NULL);
		}
	}
	return (line);
}
