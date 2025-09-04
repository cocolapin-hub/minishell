
#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft/libft.h"

typedef enum e_token_type {
	WORD,
	PIPE,					// |
    REDIR_IN,      			// <
    REDIR_OUT,     			// >
    REDIR_APPEND,  			// >>
    REDIR_HEREDOC  			// <<
}   t_token_type;


typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
}   t_token;


typedef struct s_command {
	char **args;           // tous les arguments, ex: ["ls", "-la", NULL]
    char *cmd;             // argument concerne, ex: "ls"

    t_token *in_redir;     // liste chaînée des redirections d'entrée
    t_token *out_redir;    // liste chaînée des redirections de sortie

	struct s_command *next;// prochaine commande (si pipe)
}   t_command;

void	exec_command(t_command *cmd, char **envp);
void	free_split(char **array);
char	*find_in_path(char *cmd, char **envp);

#endif


/*_________________________________________EXEMPLE_____

cat -n < in.txt | grep hello > out.txt

t_token *tokens = [
    { type: WORD,        value: "cat" },
    { type: WORD,        value: "-n" },
    { type: REDIR_IN,    value: "<" },
    { type: WORD,        value: "in.txt" },
    { type: PIPE,        value: "|" },
    { type: WORD,        value: "grep" },
    { type: WORD,        value: "hello" },
    { type: REDIR_OUT,   value: ">" },
    { type: WORD,        value: "out.txt" }
];


cmd      = "cat";
args     = ["cat", "-n", NULL];
in_redir = [ { type: REDIR_IN, filename: "in.txt" } ];
out_redir= NULL;
next     = cmd2;


cmd      = "grep";
args     = ["grep", "hello", NULL];
in_redir = NULL;
out_redir= [ { type: REDIR_OUT, filename: "out.txt" } ];
next     = NULL;
*/