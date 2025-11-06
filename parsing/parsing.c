/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 19:21:27 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check_char_in_cmd(t_command, all)
// {
// 	char s;

// 	s = ft_strbrk(cmd->list->value, ";&{}[]()*?!");
// 	if (s && list->amount == Q_NONE)
// 	{
// 		write(2, "syntax error near unexpected token `", 36);
// 		write(2, &s, 1);
// 		write(2, "'\n", 2);
// 		(*all)->last_status = 2;
// 		return (NULL);
// 	}


// }

void	end_parsing(char *line, t_token **list, t_command **cmd, int flag)
{
	free(line);
	free_tokens(*list);
	if (flag == 0)
		*cmd = NULL;
}

void	parsing(char *line, t_shell *all, t_command **cmd)
{
	char	*cleaned_line;
	t_token	*list;

	list = NULL;
	add_history(line);
	cleaned_line = check_input(line, &all);
	if (!cleaned_line)
	{
		end_parsing(cleaned_line, &list, cmd, 0);
		return ;
	}
	tokenisation(0, cleaned_line, &list, &all);
	if (!list)
	{
		end_parsing(cleaned_line, &list, cmd, 0);
		return ;
	}
	error_handling(&all, &list);
	if (!list)
	{
		end_parsing(cleaned_line, &list, cmd, 0);
		return ;
	}
	set_command(cmd, list, all);
	// check_char_in_cmd(cmd, all);
	end_parsing(cleaned_line, &list, cmd, 1);
}
