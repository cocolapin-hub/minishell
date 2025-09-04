/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:29:39 by claffut           #+#    #+#             */
/*   Updated: 2025/09/04 12:43:58 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define MAX_LINE_LEN 4096

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
//#include <  .h>
//#include <  .h>
//#include <  .h>


typedef enum e_quote {
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

typedef enum e_element {
	WORD,
	PIPE,									// |
    REDIR_IN,      							// <
    REDIR_OUT,     							// >
    REDIR_APPEND,  							// >>
    REDIR_HEREDOC				  			// <<
}   t_element;

typedef struct s_token {
    t_element 				type;
	t_quote  				amount;
	char 					*value;
    struct s_token 			*next;
}   t_token;

typedef struct s_command {
	char 					**args;        // tous les arguments, ex: ["ls", "-la", NULL]
    t_token 				*redir;		   // liste chaînée des redirs
	struct s_command 		*next;		   // prochaine commande (si pipe)
}   t_command;


/*parsing*/
void		print_error(char *line, char *msg);
char		*check_input(char *line);
t_command	*parsing(char *line);


/*executable*/

#endif



// /*_________________________________________EXEMPLE_____*/

// /*Ligne de commande*/
// cat -n < in.txt | grep hello > out.txt

// /* Liste de tokens (t_token) */
// t_token *tokens = [
//     { type: WORD,      quote: Q_NONE, value: "cat" },
//     { type: WORD,      quote: Q_NONE, value: "-n" },
//     { type: REDIR_IN,  quote: Q_NONE, value: "in.txt" },
//     { type: PIPE,      quote: Q_NONE, value: "|" },
//     { type: WORD,      quote: Q_NONE, value: "grep" },
//     { type: WORD,      quote: Q_NONE, value: "hello" },
//     { type: REDIR_OUT, quote: Q_NONE, value: "out.txt" }
// ]

// /* Construction des commandes (t_command) */
// cmd = "cat"
// args = ["cat", "-n", NULL]
// redir = [ { type: REDIR_IN, quote: Q_NONE, value: "in.txt" } ]
// next = cmd2

// cmd2 = "grep"
// args = ["grep", "hello", NULL]
// redir = [ { type: REDIR_OUT, quote: Q_NONE, value: "out.txt" } ]
// next = NULL

