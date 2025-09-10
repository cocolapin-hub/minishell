
#ifndef MINISHELL_H
#define MINISHELL_H

#define MAX_LINE_LEN 4096

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_local {
    char            		*key;     		// VAR || $HOME ETC
    char            		*value;   		// Word or PATH
    struct s_local   		*next;
}   t_local;

typedef struct s_SHELL {
    t_local           		*env;     		// VAR || $HOME ETC
    int						last_status;   	// Word or PATH
}   t_SHELL;

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
    t_token 				*redir;		   // liste chaînée des redirs (<,>,>>,...)
	t_SHELL					*all;		   // contient env et last_status
	struct s_command 		*next;		   // prochaine commande (si pipe)
}   t_command;

// t_token → pendant le parsing uniquement.
// t_command → pendant l’exécution (args + redirections + lien vers t_SHELL).
// t_SHELL → toujours accessible pour garder l’état global (env, $?).
// t_local → interne à l’env (manipulation des variables).

/*fonctions*/
t_token			*ft_lstnew_token(char *content, char quotes);
void			ft_lstadd_back(t_token **lst, t_token *new);
char			*ft_strdup(const char *s, int x, int len);
t_local			*ft_lstnew_env(char *value, char *key);
void			print_error(char *line, char *msg);
t_token			*ft_lstlast(t_token *lst);
size_t			ft_strlen(const char *s);
void			setup_signal(void);
char			*ft_itoa(int n);

/*setup*/
void			setup_shell(t_SHELL **all, char **envp);
void			setup_signal(void);

/*parsing*/
void			expansion(t_local *env, int last_status, t_token **list);
void			tokenisation(char *line, t_token **list);
t_command		*parsing(char *line, t_SHELL *all);
char			*check_input(char *line);

/*__________executable____________*/

/*ENV*/
char	*get_env_value(t_local *env, const char *key);
void    set_env_value(t_local **env, char *key, char *value);
void    unset_env_value(t_local **env, char *key);
void	free_envp(char **envp);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	**env_to_tab(t_local *env);

/*EXEC*/
void	run_command(t_command *cmd);
char	*find_in_path(char *cmd, t_local *env);
void	free_split(char **array);
void	child_process(t_command *cmd, t_local *env);

/*BUILTINS*/
int		is_builtin(char *cmd);
int		exec_builtin(t_command *cmd, t_local *env);
int		builtin_pwd(void);
int		builtin_echo(char **args);
int		builtin_export(char **args, t_local *env);
int		builtin_unset(char **args, t_local *env);
int		builtin_cd(char **args, t_local *env);
int		builtin_env(t_local *env);
int		builtin_exit(char **args);

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


