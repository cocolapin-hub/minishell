#include "../../minishell.h"

static char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	res = malloc(len1 + len2 + len3 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	ft_memcpy(res + len1 + len2, s3, len3);
	res[len1 + len2 + len3] = '\0';
	return (res);
}

static int	env_size(t_local *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}
// Cette fonction malloc chaque string et aussi le tableau. Donc faut free le tableau après usage !!
char	**env_to_tab(t_local *env)
{
	char	**tab;
	t_local	*tmp;
	int		i;

	tab = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		tab[i] = ft_strjoin3(tmp->key, "=", tmp->value);
		if (!tab[i])
			return (free_split(tab), NULL);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}
