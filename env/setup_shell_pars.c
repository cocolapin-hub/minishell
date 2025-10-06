#include "../minishell.h"

void	setup_env(t_local **env, char *tab, int len, int y)
{
	char	*value = NULL;
	char	*key = NULL;
	t_local *last;
	t_local	*new;

	len = ft_strlen(tab);
	y = 0;
	while(tab[y] && tab[y] != 61)
		y++;

	/*save key & value*/
	if (tab[y] == 0)
	{
		key = ft_strdup_m(tab, 0, y);
		value = NULL;
	}
	else
	{
		key = ft_strdup_m(tab, 0, y);
		y++;
		value = ft_strdup_m(tab, y, len - y);
	}

	/*send to env*/
	new = ft_lstnew_env(value, key);
	if (!*env)
		*env = new;
	else
	{
		last = *env;
    	while (last->next)
        	last = last->next;
    	last->next = new;
	}
}

void	setup_shell(t_shell *all, char **envp)
{

	int 	x;

	// *all = malloc(sizeof(t_shell));
	// if (!(*all))
	// 	exit (1);
	all->env = NULL;
	all->last_status = 0;

	x = 0;
	while (envp[x])
	{
		setup_env(&(all->env), envp[x], 0, 0);
		x++;
	}

}