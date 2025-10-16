
#include "../../minishell.h"

int	is_valid_identifier(const char *key)
{
	int	i;

	if (!key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	is_invalid_key(char *key, char *arg)
{
	if (!key || !is_valid_identifier(key))
	{
		print_invalid_identifier(arg);
		free(key);
		return (1);
	}
	return (0);
}

static void	print_sorted_env(t_local *env)
{
	char	**tab;
	int		i;
	char	*equal;

	tab = env_to_tab(env);
	if (!tab)
		return ;
	sort_env_tab(tab);
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		equal = ft_strchr(tab[i], '=');
		if (equal)
		{
			*equal = '\0';
			ft_putstr_fd(tab[i], 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(equal + 1, 1);
			ft_putendl_fd("\"", 1);
			*equal = '=';
		}
		else
			ft_putendl_fd(tab[i], 1);
		i++;
	}
	free_split(tab);
}

// void	print_sorted_env(t_local *env)
// {
// 	t_local	*cur;

// 	cur = env;
// 	while (cur)
// 	{
// 		if (cur->value == NULL)
// 			printf("declare -x %s\n", cur->key);
// 		else if (cur->value[0] == '\0')
// 			printf("declare -x %s=\"\"\n", cur->key);
// 		else
// 			printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
// 		cur = cur->next;
// 	}
// }

// static void	handle_export_arg(char *arg, t_local **env)
// {
// 	char	*equal;
// 	char	*key;
// 	char	*value;

// 	equal = ft_strchr(arg, '=');
// 	if (!equal)
// 	{
// 		if (!is_valid_identifier(arg))
// 			return (print_invalid_identifier(arg));
// 		if (!get_env_value(*env, arg))
// 			set_env_value(env, arg, NULL);
// 		return ;
// 	}
// 	*equal = '\0';
// 	key = ft_strdup(arg);
// 	value = ft_strdup(equal + 1);
// 	*equal = '=';
// 	if (!key || !is_valid_identifier(key))
// 		return (print_invalid_identifier(arg), free(key), free(value), (void)0);
// 	set_env_value(env, key, value);
// 	free(key);
// 	free(value);
// }


static void	handle_export_arg(char *arg, t_local **env)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		if (is_valid_identifier(arg))
			set_env_value(env, arg, NULL);
		else
			print_invalid_identifier(arg);
		return ;
	}
	*equal = '\0';
	key = ft_strdup(arg);
	value = ft_strdup(equal + 1);
	*equal = '=';
	if (is_invalid_key(key, arg))
		return (free(value), (void)0);
	if (ft_strcmp(key, "_") != 0)
		set_env_value(env, key, value);
	free(key);
	free(value);
}

int	builtin_export(char **args, t_local **env)
{
	int	i;
	int	has_valid_arg;

	if (!args[1])
		return (print_sorted_env(*env), 0);
	i = 1;
	has_valid_arg = 0;
	while (args[i])
	{
		if (args[i][0] == '\0' && !args[i][1])
		{
			i++;
			continue ;
		}
		handle_export_arg(args[i], env);
		has_valid_arg = 1;
		i++;
	}
	if (!has_valid_arg)
		print_sorted_env(*env);
	return (0);
}

/*
__________________________________________________________________________________________________________________________________________________



static int	is_valid_identifier(char *arg)
{
	int i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_sorted_env(t_local *env)
{
	t_local	**envcopy;
	t_local	*tmp;
	int		size;
	int		i;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	envcopy = malloc(sizeof(t_local *) * size);
	if (!envcopy)
		return ;
	i = 0;
	tmp = env;
	while (tmp)
	{
		envcopy[i++] = tmp;
		tmp = tmp->next;
	}	
	sort_env_tab(envcopy, size);
	i = 0;
	while (i < size)
	{
		if (envcopy[i]->value)
			printf("declare -x %s=\"%s\"\n", envcopy[i]->key, envcopy[i]->value);
		else
			printf("declare -x %s\n", envcopy[i]->key);
		i++;
	}
	free(envcopy);
}

int	builtin_export(char **args, t_local *env)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	if (!args[1])
		return (print_sorted_env(env), 0);
	i = 1; 								 // args[0] = "export"
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			printf("bash: export: '%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
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


 export $=mdr
bash: export: `$=mdr': not a valid identifier


*/