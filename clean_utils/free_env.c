
#include "../minishell.h"

void	free_env(t_shell *all)
{
	t_local *tmp1;
	t_local	*tmp2;

	if(!all || !all->env)
		return;

	/*free chaque maillon env*/
	tmp1 = all->env;
	while(tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1->key);
		free(tmp1->value);
		free(tmp1);
		tmp1 = tmp2;
	}
	all->env = NULL;
}
