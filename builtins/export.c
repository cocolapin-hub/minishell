
#include "../minishell.h"

static void	export_error(char *arg) // affiche les messages d'erreurs
{
	write(2, "minishell: export: '", 21);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

static int	is_valid_identifier(char *key) // verif si la variable commence par une lettre ou un '_' puis "lettres/chiffres/_"
{

}

static void	print_env_export(char **env) // affiche toutes les variables comme bash
{

}

static void	export_assign(char *arg, char ***env) // gere la logique KEY=VALUE
{

}

int	builtin_export(char **args, char **env) // execute export
{

}


/*	cas de figure :

1:	export (sans arguments)	→	afficher toutes les variables d’environnement.
2:	export KEY=VALUE		→	ajouter ou mettre à jour une variable dans env.
3:	export KEY				→	exporter une variable vide (KEY=).

1) minishell$ export
	declare -x PATH="/usr/bin:/bin"
	declare -x HOME="/home/user"
	... etc

2) minishell$ export TEST=hello
	minishell$ echo $TEST
	hello

3)minishell$ export FOO
	minishell$ echo $FOO

	minishell$ export 123ABC=bad
	minishell: export: `123ABC=bad': not a valid identifier

*/