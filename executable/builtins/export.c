
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

static int	is_invalid_key(char *key, char *arg, t_shell *all)
{
	if (!key || !is_valid_identifier(key))
	{
		print_invalid_id(arg, all);
		free(key);
		return (1);
	}
	return (0);
}

static void	print_sorted_env(t_local *env)
{
	char	**tab;
	int		i;

	tab = env_to_tab(env);
	if (!tab)
		return ;
	sort_env_tab(tab);
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		print_export_var(tab[i]);
		i++;
	}
	free_split(tab);
}

static int	handle_export_arg(char *arg, t_local **env, t_shell *all)
{
	char	*equal;
	char	*key;
	char	*value;

	if (!arg || arg[0] == '\0')
		return (print_invalid_id(arg, all), 1);
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		if (is_valid_identifier(arg))
			set_env_value(env, arg, NULL);
		else
			print_invalid_id(arg, all);
		return (all->last_status);
	}
	*equal = '\0';
	key = ft_strdup(arg);
	value = ft_strdup(equal + 1);
	*equal = '=';
	if (is_invalid_key(key, arg, all))
		return (free(value), 1);
	if (ft_strcmp(key, "_") != 0)
		set_env_value(env, key, value);
	return (free(key), free(value), 0);
}

int	builtin_export(char **args, t_local **env, t_shell *all)
{
	int	i;
	int	has_error;

	if (!args[1])
		return (print_sorted_env(*env), 0);
	i = 1;
	has_error = 0;
	while (args[i])
	{
		if (handle_export_arg(args[i], env, all))
			has_error = 1;
		i++;
	}
	all->last_status = has_error;
	return (has_error);
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


 export $=mdr
bash: export: `$=mdr': not a valid identifier


*/