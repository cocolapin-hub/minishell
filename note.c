/* ========== parsing/set_token/handles_command.c ========== */
#include "../../minishell.h"

void	set_values(char *line, char *quote, int *was_in_quotes, int x)
{
	*quote = line[x];
	*was_in_quotes = 1;
}

int	parse(char *line, t_cmd_state *cmd, t_shell **all, t_token **list)
{
	int		tmp_x;
	char	*tmp;

	while (line[cmd->x])
	{
		if (line[cmd->x] == 32 || line[cmd->x] == 9 || line[cmd->x] == 124
			|| line[cmd->x] == 60 || line[cmd->x] == 62)
			break ;
		tmp_x = cmd->x;
		if (line[cmd->x] == 39 || line[cmd->x] == 34)
		{
			set_values(line, &cmd->quote, &cmd->was_in_quotes, cmd->x);
			tmp = between_quotes(line, &cmd->x, all, list);
		}
		else
			tmp = outside_quotes(line, &cmd->x, all, list);
		if (!tmp)
			return (-1);
		if (tmp == SKIP_TOKEN && check_ambiguous(line, tmp_x, list, all) == 1)
			return (-1);
		if (tmp == SKIP_TOKEN)
			return (1);
		tmp = cmd->cmd;
		cmd->cmd = ft_strjoin(tmp, tmp);
		free(tmp);
		if (!cmd->cmd)
			return (-1);
	}
	return (0);
}

int	handles_command(char *line, int x, t_token **list, t_shell **all)
{
	t_cmd_state	cmd_state;
	int			status;

	cmd_state.cmd = ft_strdup("");
	if (!cmd_state.cmd)
		return (-1);
	cmd_state.x = x;
	cmd_state.was_in_quotes = 0;
	cmd_state.quote = 0;
	status = parse(line, &cmd_state, all, list);
	if (status == -1)
	{
		free(cmd_state.cmd);
		return (-1);
	}
	if (status == 1)
	{
		free(cmd_state.cmd);
		return (cmd_state.x);
	}
	if (!cmd_state.was_in_quotes && ft_strchr(cmd_state.cmd, ' '))
		token_flag_off(cmd_state.cmd, cmd_state.quote, list);
	else
		token_flag_on(cmd_state.cmd, cmd_state.quote, list);
	return (cmd_state.x);
}

/* ========== parsing/set_token/token_flag.c ========== */
#include "../../minishell.h"

static void	free_split_and_cmd(char **split, char *cmd)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
	free(cmd);
}

void	token_flag_off(char *cmd, int quote, t_token **list)
{
	char	**split;
	t_token	*new;
	int		i;

	split = ft_split(cmd, ' ');
	if (!split)
	{
		free(cmd);
		return ;
	}
	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) > 0)
		{
			new = ft_lstnew_token(split[i], quote);
			if (!new)
			{
				free_split_and_cmd(split, cmd);
				return ;
			}
			if (!*list)
				*list = new;
			else
				ft_lstadd_back(list, new);
		}
		i++;
	}
	free_split_and_cmd(split, cmd);
}

void	token_flag_on(char *cmd, int quote, t_token **list)
{
	t_token	*new;

	new = ft_lstnew_token(cmd, quote);
	if (!new)
	{
		free(cmd);
		return ;
	}
	if (!*list)
		*list = new;
	else
		ft_lstadd_back(list, new);
}

/* ========== parsing/set_token/expansion/split_expansion.c ========== */
#include "../../../minishell.h"

static char	**make_splits(char *str, char *key, int start, char *key_value)
{
	size_t	k_len;
	size_t	s_len;
	char	**splits;

	splits = malloc(sizeof(char *) * 3);
	if (!splits)
		return (NULL);
	if (key[0] == '$')
		k_len = strlen(key);
	else
		k_len = strlen(key) + 1;
	s_len = strlen(str);
	if (start == 0)
		splits[0] = ft_strdup("");
	else
		splits[0] = ft_strdup_m(str, 0, start);
	splits[1] = ft_strdup(key_value);
	if (start + k_len < s_len)
		splits[2] = ft_strdup_m(str, start + k_len, s_len - (start + k_len));
	else
		splits[2] = ft_strdup("");
	if (!splits[0] || !splits[1] || !splits[2])
	{
		free(splits[0]);
		free(splits[1]);
		free(splits[2]);
		free(splits);
		return (NULL);
	}
	return (splits);
}

static void	free_splits(char **splits)
{
	if (splits)
	{
		free(splits[0]);
		free(splits[1]);
		free(splits[2]);
		free(splits);
	}
}

char	*split_expansion(char *str, char *key, int start, char *key_value)
{
	char	**splits;
	char	*tmp;
	char	*result;

	splits = make_splits(str, key, start, key_value);
	if (!splits)
		return (NULL);
	tmp = ft_strjoin(splits[0], splits[1]);
	if (!tmp)
	{
		free_splits(splits);
		return (NULL);
	}
	result = ft_strjoin(tmp, splits[2]);
	free(tmp);
	free_splits(splits);
	if (!result)
		return (NULL);
	return (result);
}

/* ========== parsing/set_token/between_quotes.c ========== */
#include "../../minishell.h"

static void	expand_word(char **tmp, char quote, t_shell **all, t_token **list)
{
	t_token	*last;
	char	*expanded;

	last = NULL;
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}
	if (quote != 39 && (!last || last->type != REDIR_HEREDOC))
	{
		expanded = expansion((*all)->env, (*all)->last_status, *tmp, &quote);
		if (!expanded)
		{
			free(*tmp);
			*tmp = NULL;
			return ;
		}
		free(*tmp);
		*tmp = expanded;
	}
}

char	*between_quotes(char *line, int *x, t_shell **all, t_token **list)
{
	char	quote;
	char	*tmp;
	int		y;

	y = *x + 1;
	quote = line[*x];
	if (line[y] == quote)
	{
		*x += 2;
		return (ft_strdup(""));
	}
	while (line[y] && line[y] != quote)
		y++;
	if (line[y] == '\0')
	{
		write(2, "syntax error: unclosed quotes\n", 30);
		(*all)->last_status = 258;
		return (NULL);
	}
	tmp = ft_strdup_m(line, *x + 1, y - *x - 1);
	if (!tmp)
		return (NULL);
	expand_word(&tmp, quote, all, list);
	*x = y + 1;
	return (tmp);
}

/* ========== parsing/set_token/outside_quotes.c ========== */
#include "../../minishell.h"

static void	expand_word(char **tmp, char quote, t_shell **all, t_token **list)
{
	t_token	*last;
	char	*expanded;

	last = NULL;
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
	}
	if (!last || last->type != REDIR_HEREDOC)
	{
		expanded = expansion((*all)->env, (*all)->last_status, *tmp, &quote);
		if (!expanded)
		{
			free(*tmp);
			*tmp = NULL;
			return ;
		}
		free(*tmp);
		*tmp = expanded;
	}
}

char	*outside_quotes(char *line, int *x, t_shell **all, t_token **list)
{
	int		start;
	char	*tmp;
	int		y;

	tmp = NULL;
	y = *x;
	if (line[y] == '$' && (line[y + 1] == 34 || line[y + 1] == 39))
	{
		(*x)++;
		return (ft_strdup(""));
	}
	else
	{
		start = find_word(&y, *x, line, &tmp);
		if (!tmp)
			return (NULL);
		expand_word(&tmp, 0, all, list);
		if (!tmp)
			return (NULL);
	}
	if (line[start] == '$' && ft_strcmp(tmp, "") == 0)
	{
		*x = y;
		free(tmp);
		return (SKIP_TOKEN);
	}
	*x = y;
	return (tmp);
}

/* ========== parsing/set_cmd/create_cmd.c ========== */
#include "../../minishell.h"

void	create_cmd(t_token **tmp, t_token **new, t_token **start, t_token **end)
{
	t_token	*target;

	target = (*tmp)->next;
	while (target && target->type == WORD && target->value[0] == '-')
		target = target->next;
	if (target && target->type == WORD)
	{
		*new = malloc(sizeof(t_token));
		if (!*new)
			return ;
		(*new)->type = (*tmp)->type;
		(*new)->value = ft_strdup(target->value);
		if (!(*new)->value)
		{
			free(*new);
			*new = NULL;
			return ;
		}
		(*new)->amount = target->amount;
		(*new)->next = NULL;
		if (!(*start))
			*start = *new;
		else
			(*end)->next = *new;
		*end = *new;
		*tmp = target;
	}
}