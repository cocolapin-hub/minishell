
#include "../../minishell.h"

int	builtin_pwd(void)
{
	char	cwd[4096]; 					  // buffer pour stocker le chemin absolu ecrit depuis getcwd

	if (getcwd(cwd, sizeof(cwd)) != NULL) // si ca echoue return NULL donc appelle perror
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

/*

faire attention au scénario ou env n'est pas setup et PWD= n'existe pas

*/