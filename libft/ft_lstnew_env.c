
#include "../minishell.h"

t_local	*ft_lstnew_env(char *value, char *key)
{
	t_local	*node;

	node = malloc(sizeof(t_local));
	if (!node)
		exit(1);
	node->value = value;
	node->key = key;
	node->next = NULL;
	return (node);
}
