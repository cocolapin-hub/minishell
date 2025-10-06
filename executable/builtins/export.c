
#include "../../minishell.h"

// static void	export_error(char *arg) // affiche les messages d'erreurs
// {
// 	write(2, "minishell: export: '", 21);
// 	write(2, arg, ft_strlen(arg));
// 	write(2, "': not a valid identifier\n", 26);
// }
// static int	is_valid_identifier(char *key) // verif si la variable commence par une lettre ou un '_' puis "lettres/chiffres/_"
// static void	print_env_export(char **env) // affiche toutes les variables comme bash
// static void	export_assign(char *arg, char ***env)


int	builtin_export(char **args, t_local *env)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	i = 1; 								 // args[0] = "export"
	while (args[i])
	{
		equal = ft_strchr(args[i], '='); // pointe sur le '=' dans la chaîne
		if (!equal)						 // si pas de =, on ignore et on passe à args suivant
		{
			i++;
			continue;
		}
		*equal = '\0';					 // On remplace le '=' par un caractère '\0'. pour terminer la chaine. donc "PATH=/bin" devient deux chaînes (evite de faire un new malloc)
		key = args[i];					 // apres le \0, key pointe uniquement sur "KEY" (ex : key = "PATH")
		value = equal + 1;				 // equal pointe sur \0, +1 c'est la position apres donc "VALUE" (Exemple : "PATH=/bin" → value = "/bin")
		set_env_value(&env, key, value); // maj de la variable dans la liste chainée
		*equal = '=';					 // on remet le '=' pour ne pas modifier largs original (args[i]) et pouvoir réutiliser la chaine
		i++;							 // args suivant
	}
	return (0);
}

/*

	Objectif
		Si la variable existe déjà → mettre à jour sa valeur.
		Sinon → créer un nouveau maillon dans la liste.
		Syntaxe : export KEY=VALUE

cas de figure :

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

3)minishell$ export FOO	→ minishell$ echo $FOO	→	(rien, retour a la ligne)

	minishell$ export 123ABC=bad
	minishell: export: `123ABC=bad': not a valid identifier

*/