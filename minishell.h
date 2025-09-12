/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:29:39 by claffut           #+#    #+#             */
/*   Updated: 2025/09/12 15:14:05 by ochkaoul         ###   ########.fr       */
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

typedef struct s_local {					// my env_
    char            		*key;     		// VAR || $HOME ETC
    char            		*value;   		// Word or PATH
    struct s_local   		*next;
}   t_local;

typedef struct s_SHELL {
    t_local           		*env;     		// VAR || $HOME ETC
    int						last_status;   	// Word or PATH
}   t_SHELL;

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
	char 					*value;
    struct s_token 			*next;
}   t_token;

typedef struct s_command {
	char 					**args;        // tous les arguments, ex: ["ls", "-la", NULL]
    t_token 				*redir;		   // liste chaînée des redirs
	t_SHELL					*all;
	struct s_command 		*next;		   // prochaine commande (si pipe)
}   t_command;


/*fonctions*/
void			ft_lstadd_back(t_token **lst, t_token *new);
char			*ft_strdup_m(const char *s, int x, int len);
char			*ft_strjoin(char *s1, char const *s2);
t_local			*ft_lstnew_env(char *value, char *key);
void			print_error(char *line, char *msg);
t_token			*ft_lstnew_token(char *content);
t_token			*ft_lstlast(t_token *lst);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *s);
void			setup_signal(void);
char			*ft_itoa(int n);

/*setup*/
void			setup_shell(t_SHELL **all, char **envp);
void			setup_signal(void);

/*parsing*/
char			*expansion(t_local *env, int last_status, char *str, char quote);
void			tokenisation(char *line, t_token **list, t_SHELL **all);
//void 			error_handling(t_SHELL **all, t_token **list);
t_command		*parsing(char *line, t_SHELL *all);
char			*check_input(char *line);


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

