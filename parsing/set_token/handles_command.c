
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
		cmd->cmd = ft_strjoin_free(cmd->cmd, tmp);
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
