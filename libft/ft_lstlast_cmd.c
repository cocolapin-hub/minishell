
#include "../minishell.h"

t_command	*ft_lstlast_cmd(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
