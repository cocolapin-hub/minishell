
#include "../../minishell.h"

void	create_cmd(t_token **tmp, t_token **new, t_token **start, t_token **end)
{
	t_token	*target;

	target = (*tmp)->next;
	while (target && target->type == WORD && target->value[0] == '-')
		target = target->next;
	if (target && target->type == WORD)
	{
		*new = malloc(sizeof(t_token));
		if (!new)
			return ;
		(*new)->type = (*tmp)->type;
		(*new)->value = ft_strdup(target->value);
		if (!(*new)->value)
		{
			free(*new);
			*new = NULL;
			return ;
		}
		(*new)->amount = target->amount;
		(*new)->next = NULL;
		if (!(*start))
			*start = *new;
		else
			(*end)->next = *new;
		*end = *new;
		*tmp = target;
	}
}
