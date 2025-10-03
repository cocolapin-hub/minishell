#include "../minishell.h"

void	ft_lstadd_back_cmd(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_cmd(*lst);
	last->next = new;
}