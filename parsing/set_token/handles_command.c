
#include "../../minishell.h"

void	token_flag_off(char *cmd, int quote, t_token **list)
{
	char	**split;
	t_token	*new;
	int		i;

	i = 0;
	split = ft_split(cmd, ' ');
	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) > 0)
		{
			new = ft_lstnew_token(split[i], quote);
			if (!*list)
				*list = new;
			else
				ft_lstadd_back(list, new);
		}
		i++;
	}
	free(cmd);
}

void	token_flag_on(char *cmd, int quote, t_token **list)
{
	t_token	*new;

	new = ft_lstnew_token(cmd, quote);
	if (!*list)
		*list = new;
	else
		ft_lstadd_back(list, new);
}

void	set_values(char *line, char *quote, int *was_in_quotes, int x)
{
	*quote = line[x];
	*was_in_quotes = 1;
}

int	parse(char *line, t_cmd_state *cmd_state, t_shell **all, t_token **list)
{
	char	*tmp;
	int		tmp_x;

	while (line[cmd_state->x])
	{
		if (line[cmd_state->x] == 32 || line[cmd_state->x] == 9 ||
			line[cmd_state->x] == 124 || line[cmd_state->x] == 60
			|| line[cmd_state->x] == 62)
			break ;
		tmp_x = cmd_state->x;
		if (line[cmd_state->x] == 39 || line[cmd_state->x] == 34)
		{
			set_values(line, &cmd_state->quote, &cmd_state->was_in_quotes,
				cmd_state->x);
			tmp = between_quotes(line, &cmd_state->x, all, list);
		}
		else
			tmp = outside_quotes(line, &cmd_state->x, all, list);
		if (!tmp)
			return (-1);
		if (tmp == SKIP_TOKEN)
		{
			if (check_ambiguous(line, tmp_x, list, all) == 1)
				return (-1);
			return (1);
		}
		cmd_state->cmd = ft_strjoin_free(cmd_state->cmd, tmp);
		// free(tmp);
	}
	return (0);
}

int	handles_command(char *line, int x, t_token **list, t_shell **all)
{
	t_cmd_state	cmd_state;
	int			status;

	cmd_state.cmd = ft_strdup("");
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
