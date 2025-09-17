
#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_local	*new_env_node(char *key, char *value) // duplique key et value pour éviter de modifier l’original envp.
{
	t_local	*node;

	node = malloc(sizeof(t_local));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;						 // next = NULL car c’est un maillon isolé pour l’instant.
	return (node);
}

void	add_env_node(t_local **env, t_local *new_node)
{
	t_local	*tmp;

	if (!env || !new_node)
		return ;
	if (!*env) 			  // Si la liste est vide
	{
		*env = new_node;  // le nouveau devient la tête.
		return ;
	}
	tmp = *env;
	while (tmp->next)	  // on parcourt jusqu’au dernier
		tmp = tmp->next;
	tmp->next = new_node; // et on relie
}

t_local	*env_init(char **envp)
{
	t_local	*env;
	t_local	*node;
	int		i;
	char	*eq;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '='); 			  // strchr pointe vers sur '='
		if (eq)
		{
			*eq = '\0'; 						  // coupe la string "PATH=/bin" -> "PATH" et "/bin"
			node = new_env_node(envp[i], eq + 1); // crée node {key=PATH, value=/bin}
			*eq = '='; 							  // remet le '=' pour pas casser envp original
			add_env_node(&env, node);
		}
		i++;
	}
	return (env);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    // === Initialiser l'environnement ===
    t_SHELL all;
    all.env = env_init(envp);
    all.last_status = 0;

    // === Exemple 1 : une seule commande ===
    t_command cmd1;
    char *args1[] = {"ls", "-l", NULL};

    cmd1.args = args1;
    cmd1.redir = NULL;
    cmd1.all = &all;
    cmd1.next = NULL;

    printf("\n--- Test 1 : commande simple ---\n");
    run_command(&cmd1);
    printf("last_status = %d\n", all.last_status);

    // === Exemple 2 : pipeline "ls -l | grep minishell" ===
    t_command cmd2;
    t_command cmd3;
    char *args2[] = {"ls", "-l", NULL};
    char *args3[] = {"grep", "minishell", NULL};

    cmd2.args = args2;
    cmd2.redir = NULL;
    cmd2.all = &all;
    cmd2.next = &cmd3;

    cmd3.args = args3;
    cmd3.redir = NULL;
    cmd3.all = &all;
    cmd3.next = NULL;

    printf("\n--- Test 2 : pipeline ---\n");
    exec_pipe(&cmd2, &all);
    printf("last_status = %d\n", all.last_status);

    // === Exemple 3 : builtin "pwd" ===
    t_command cmd4;
    char *args4[] = {"pwd", NULL};

    cmd4.args = args4;
    cmd4.redir = NULL;
    cmd4.all = &all;
    cmd4.next = NULL;

    printf("\n--- Test 3 : builtin ---\n");
    run_command(&cmd4);
    printf("last_status = %d\n", all.last_status);

    return 0;
}







/*
 readline → pour lire la ligne.
 find_in_path → pour trouver la commande.
 exec_command → pour exécuter.
*/













