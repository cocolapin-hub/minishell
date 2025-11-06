/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 20:48:28 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (end_parsing(cleaned_line, &list, cmd, 0), (void)0);
	tokenisation(0, cleaned_line, &list, &all);
	if (!list)
		return (end_parsing(cleaned_line, &list, cmd, 0), (void)0);
	error_handling(&all, &list);
	if (!list)
		return (end_parsing(cleaned_line, &list, cmd, 0), (void)0);
	set_command(cmd, list, all);
	if (!check_special(*cmd, all))
		*cmd = NULL;
	end_parsing(cleaned_line, &list, cmd, 1);
}
