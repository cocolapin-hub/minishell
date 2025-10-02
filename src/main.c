
#include "../minishell.h"

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

// void executor(t_command *cmd_list, t_SHELL *all)
// {
//     if (!cmd_list)
//         return;
//     if (cmd_list->next)
//         exec_pipe(cmd_list, all);
//     else
//         run_command(cmd_list);
// }

// int g_in_heredoc = 0; // flag global pour savoir si on est dans un heredoc qu'on integrera a la structure t_SHELL plus tard (sinon = 1 pendant la lecture dans create_heredoc)

int main(int argc, char **argv, char **envp)
{
    t_SHELL 	all;
    t_command 	*cmd_list = NULL;
    char 		*line;

    (void)argc;
    (void)argv;

    all.env = init_env(envp);
    all.last_status = 0;
    setup_sig();

    while (1)
    {
        line = readline("minishell$ ");
		if (!line)
		{
			if (g_in_heredoc == SIGINT)
			{
				g_in_heredoc = 0;
				continue ;
			}
			printf("exit\n");
			exit_clean_af(&all, cmd_list, all.last_status);
		}
		if (line[0] != '\0')
			add_history(line);


        // ex: cmd_list = parsing(line, &all);		PARSING | TOKENIZING | EXPANSION

        free(line);

        if (!cmd_list)
            continue;

        // Exécution (ta partie)
        if (cmd_list->next) // il y a un pipe
            exec_pipe(cmd_list, &all);
        else
            run_command(cmd_list);

        free_command(cmd_list);
        cmd_list = NULL;
    }

    clear_history();
    free_env(all.env);
    return (0);
}

/*

EXEMPLE avec expansion :	echo $HOME > $FILE

PARSING :					cmd->args = {"echo", "/home/claffut", NULL};
							cmd->elem (redir) = {type=REDIR_OUT, value="out.txt"};


CAS PARTICULIERS :

	echo $ et "$"	:	affiche $ (parsing doit check si c'est avec echo ?)

	echo "$BICHE"	:	affiche "" (chaine vide, pas supprimée car entre quotes) ( " = expans activée | ' = expans désactivée )

	PATH= "a b c"
	echo  $PATH		:	 a b c	(3 arguments)
	echo "$PATH"	:	"a b c"	(1 argument)

	cat << 	EOF
	$USER			:	affiche claffut
	EOF

	cat << 'EOF'
	$USER			:	affiche $USER
	EOF

	FILE="out.txt"
	echo coucou > $FILE		:	écrit dans out.txt

	lol > $26CM		:	affiche ->	bash: $26CM: ambigous redirect

	/bin/cd			:	bash: /bin/cd: No such file or directory

	exit lol		:	exit
						bash: exit: lol: numeric argument required ($? = 2)
	exit 19			: suivi d'un echo $? donne : last_status = 19

	/bin/ls mdr		:	/bin/ls: cannot access 'mdr': No such file or directory ($? = 2)
	
	$? / $?			:	0: command not found

	CTRL-C			:	^C + nouvelle ligne avec nouveau prompt

	CTRL-D			:	apres avoir écrit quelque chose : ne fait rien.		sinon quitte minishell

	cat (sans arg)	
	ctrl-c			:	interrompt la commande bloquante + ^C 					+ new prompt
	ctrl-\			:	interrompt la commande bloquante + ^\Quit (core dumped) + new prompt
	ctrl-d			:	interrompt la commande bloquante + new prompt (sans quitter minishell)

	ls  "src/"		:	marche
	ls '"src/"'		:	ls: cannot access '"src/"': No such file or directory

	$ cat > | ls	:	bash: syntax error near unexpected token `|' 	(la parsing devrait donner un token REDIR_OUT null : redir->value == NULL)


*/