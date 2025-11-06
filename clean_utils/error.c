/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/06 21:38:57 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_error(char *file, char *msg)
{
	print_err(NULL, file, msg);
	return (1);
}

void	print_invalid_id(char *arg, t_shell *all)
{
	write(2, "export: `", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	all->last_status = 1;
}

void	fatal_exit(const char *msg, int code)
{
	perror(msg);
	_exit(code);
}

void	print_signal_message(t_shell *all)
{
	if (all->last_status == 128 + SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (all->last_status == 128 + SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}
