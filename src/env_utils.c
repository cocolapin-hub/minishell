
#include "../minishell.h"

char    *get_env_value(t_local *env, const char *key) // recoit la valeur du pointeur vers la tete de liste, peut lire et modifier les champs des noeuds, affecte la lst d'origine mais ne peut pas changer la valeur du pointeur comme créer un new node
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

void    set_env_value(t_local **env, char *key, char *value) // pointeur vers le pointeur tete, peut lire la list via *env ET modifier la tete (*env = new_node)
{
    t_local   *node;

    node = *env;
    while (node)
    {
        if (ft_strcmp(node->key, key) == 0)
        {
            free(node->value);
            node->value = ft_strdup(value);
            return ;
        }
        node = node->next;
    } // si pas trouvé, on crée un nouveau maillon
    node = malloc(sizeof(t_local));
    if (!node)
        return ;
    node->key = ft_strdup(key);
    node->value = ft_strdup(value);
    node->next = *env;
    *env = node;
}

void    unset_env_value(t_local **env, char *key) // *env : lecture seule ou modif d'un noeud existant | **env : possibilité de changer la tete ou changer env elle meme
{
    t_local   *prev;
    t_local   *cur;

    prev = NULL;
    cur = *env;
    while (cur)
    {
        if (ft_strcmp(cur->key, key) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                *env = cur->next;
            free(cur->key);
            free(cur->value);
            free(cur);
            return ;
        }
        prev = cur;
        cur = cur->next;
    }
}

void	free_split(char **array)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_envp(char **envp) // same shit que free_split, a merge plus tard
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
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

#include <stdlib.h>

char	**env_to_tab(t_local *env)
{
	char	**tab;
	char	*joined;
	int		size;
	int		i;
	t_local	*tmp;

	size = 0;
	tmp = env;
	while (tmp)									// 1. Compter le nombre de variables
	{
		size++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (size + 1));	// 2. Allouer le tableau (+1 pour NULL)
	if (!tab)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp) 								// 3. Remplir avec "KEY=VALUE"
	{
		joined = ft_strjoin3(tmp->key, "=", tmp->value);
		tab[i++] = joined;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
} // Cette fonction malloc chaque string et aussi le tableau. Donc faut free le tableau après usage !!

