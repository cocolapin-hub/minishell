
#include "../minishell.h"

void	free_command(t_command *cmd)
{
	t_command	*tmp;
	t_token		*tok;
	t_token		*next_tok;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_split(cmd->args);
		tok = cmd->elem;
		while (tok)
		{
			next_tok = tok->next;
			free(tok->value);
			free(tok);
			tok = next_tok;
		}
		free(cmd);
		cmd = tmp;
	}
}

void	free_env(t_local *env)
{
	t_local	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		fee(env);
		env = tmp;
	}
}

void	fatal_error(const char *msg, int code)
{
	perror(msg);
	exit(code);
}

void	exit_clean_af(t_SHELL *all, t_command *cmd_list, int code)
{
	if (cmd_list)
		free_command(cmd_list);
	if (all->env)
		free_env(all->env);
	exit(code);
}