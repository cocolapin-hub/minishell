/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:29:39 by claffut           #+#    #+#             */
/*   Updated: 2025/09/03 11:14:26 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

typedef enum e_quote_kind { Q_NONE, Q_SINGLE, Q_DOUBLE } t_quote_kind;

typedef enum e_token_type {
	WORD,
	PIPE,									// |
    REDIR_IN,      							// <
    REDIR_OUT,     							// >
    REDIR_APPEND,  							// >>
    REDIR_HEREDOC				  			// <<
}   t_token_type;


typedef struct s_token {
    t_token_type 			type;
	t_quote_kind  			quote;
	char 					*value;
    struct s_token 			*next;
}   t_token;


typedef struct s_command {
	char 					**args;        // tous les arguments, ex: ["ls", "-la", NULL]
    t_token 				*redir;		   // liste chaînée des redirs
	struct s_command 		*next;		   // prochaine commande (si pipe)
}   t_command;

#endif


/*_________________________________________EXEMPLE_____*/

/*Ligne de commande*/
cat -n < in.txt | grep hello > out.txt

/* Liste de tokens (t_token) */
t_token *tokens = [
    { type: WORD,      quote: Q_NONE, value: "cat" },
    { type: WORD,      quote: Q_NONE, value: "-n" },
    { type: REDIR_IN,  quote: Q_NONE, value: "in.txt" },
    { type: PIPE,      quote: Q_NONE, value: "|" },
    { type: WORD,      quote: Q_NONE, value: "grep" },
    { type: WORD,      quote: Q_NONE, value: "hello" },
    { type: REDIR_OUT, quote: Q_NONE, value: "out.txt" }
]

/* Construction des commandes (t_command) */
cmd = "cat"
args = ["cat", "-n", NULL]
redir = [ { type: REDIR_IN, quote: Q_NONE, value: "in.txt" } ]
next = cmd2

cmd2 = "grep"
args = ["grep", "hello", NULL]
redir = [ { type: REDIR_OUT, quote: Q_NONE, value: "out.txt" } ]
next = NULL