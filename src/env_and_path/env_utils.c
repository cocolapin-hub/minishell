#include "../../minishell.h"

// recoit la valeur du pointeur vers la tete de liste, peut lire et modifier les champs des noeuds, affecte la lst d'origine mais ne peut pas changer la valeur du pointeur comme créer un new node
char    *get_env_value(t_local *env, char *key)
{
    while (env) 
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}
// pointeur vers le pointeur tete, peut lire la list via *env ET modifier la tete (*env = new_node)
void    set_env_value(t_local **env, char *key, char *value)
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
// *env : lecture seule ou modif d'un noeud existant | **env : possibilité de changer la tete ou changer env elle meme
void    unset_env_value(t_local **env, char *key)
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

