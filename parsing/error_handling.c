/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/11 11:03:56 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pipe()
{
//	| au début ou à la fin
}
void	check_heredoc()
{
//	Heredoc sans délimiteur
}
void	check_redir()
{
//	>, <, >>, << sans mot après
//	Deux redirections consécutives sans mot au milieu
}
void	check_quotes()
{
//	quotes non ferme
}

void 	check_if_unkown()
{
//	si tu recoit un || ou && par exemple
}

void	error_handling(t_token *list)
{

	// grande loop qui appliqur a chaque token chaque fonctions
	//when error found then change $? ?
}