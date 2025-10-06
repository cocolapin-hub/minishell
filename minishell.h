#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_LINE_LEN 4096

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <stdint.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

extern int		g_in_heredoc;

typedef struct s_local {
    char            		*key;     		// VAR || $HOME ETC
    char            		*value;   		// Word or PATH
    struct s_local   		*next;
}   t_local;

typedef struct s_shell {
    t_local           		*env;     		// VAR || $HOME ETC
    int						last_status;   	// Word or PATH
}   t_shell;

typedef enum e_quote {
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

typedef enum e_type {						//element dans parsing
	WORD,
	PIPE,									// |
    REDIR_IN,      							// <
    REDIR_OUT,     							// >
    REDIR_APPEND,  							// >>
    REDIR_HEREDOC				  			// <<
}   t_type;

typedef struct s_token {
    t_type 					type;			// word, opérateur (|), ou redirection
	t_quote  				amount;			// si le mot est entouré de ' ou "
	char 					*value;			// contenu textuel (ls, "hello", '*.c' etc)
    struct s_token 			*next;
}   t_token;

typedef struct s_command {					//names are differents here too
	char 					**args;        // tous les arguments, ex: ["ls", "-la", NULL] à passer à execve ou à builtin
    t_token 				*elem;		   // liste chaînée des redirs (<,>,>>,...)
	t_shell					*all;		   // contient env et last_status
	struct s_command 		*next;		   // prochaine commande (si pipe)
}   t_command;

typedef struct s_pipe
{
	int						prev_fd;		// stdin par défaut si pas de pipe avant ( -1 : valeur sentinelle)
	int						pipefd[2];
	pid_t					last_pid;		// on garde le dernier enfant (dernier fork qui est la commande la plus à droite du pipe) on doit l'utiliser pour $?
	pid_t					pid;
	t_command				*cmd_list;
}	t_pipe;


/*_______________________________environnement_______________________________*/
/*PARS*/ //--> on garde celui ci
void			setup_shell(t_shell *all, char **envp);

/*EXEC*/
//t_local			*env_init(char **envp);

/*ENV*/ //--> pour les fonction en rapport avec env
void    		set_env_value(t_local **env, char *key, char *value);
void   		 	unset_env_value(t_local **env, char *key);
char			*get_env_value(t_local *env, char *key);
char			**env_to_tab(t_local *env);



/*__________________________________signal__________________________________*/
/*PARS*/
void			setup_signal(void);

/*EXEC*/ //--> on garde celui ci
void 			setup_heredoc_signals(void);
void			sigquit_handler(int sig);
void			sigint_handler(int sig);
void			sigint_heredoc(int sig);
void			setup_sig(void);



/*_________________________________parsing_________________________________*/
/*PARS*/
char			*expansion(t_local *env, int last_status, char *str, int x);
t_command		*set_command(t_command **cmd, t_token *list, t_shell *all);
t_token			*tokenisation(char *line, t_token **list, t_shell **all);
void 			error_handling(t_shell **all, t_token **list);
t_command		*parsing(char *line, t_shell *all);
char			*check_input(char *line);

/*FREE & ERROR*/
void			print_error(char *line, char *msg);
void			free_tokens(t_token *list);
void			end_code(t_command *cmd);
void			free_args(char **args);



/*________________________________executable________________________________*/
/*EXEC*/
void			exec_pipe(t_command *cmd_list, t_shell *all);
void			child_process(t_command *cmd, t_local *env);
char			*find_in_path(char *cmd, t_local *env);
void			run_command(t_command *cmd);
/*BUILTINS*/
int 			builtin_exit(char **args, t_shell *all, t_command *cmd_list);
int				builtin_export(char **args, t_local *env);
int				builtin_unset(char **args, t_local *env);
int				builtin_cd(char **args, t_local *env);
int				exec_builtin(t_command *cmd);
int				builtin_echo(char **args);
int				is_builtin(char *cmd);
int				builtin_pwd(void);
int				builtin_env(t_local *env);


/*REDIR*/
int				apply_redir(t_token *redir, t_shell *all);
int				create_heredoc(char *limiter);

/*ERROR & FREE*/
void			exit_clean_af(t_shell *all, t_command *cmd_list, int code);
int				exec_error(const char *cmd, const char *msg, int code);
void			fatal_error(const char *msg, int code);
int				redir_error(char *file, char *msg);
void			print_error_exec(char *cmd, char *msg);
void			free_command(t_command *cmd);
void			free_split(char **array);



/*_________________________________exit_________________________________*/
void			free_env(t_shell *all);



/*________________________________LIBFT________________________________*/
t_command		*ft_lstnew_cmd(char **args, t_token *elements, t_shell *all);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
void			ft_lstadd_back_cmd(t_command **lst, t_command *new);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_strstr(const char *big, const char *little);
void			ft_lstadd_back(t_token **lst, t_token *new);
char			*ft_strdup_m(const char *s, int x, int len);
t_local			*ft_lstnew_env(char *value, char *key);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strjoin(char *s1, char const *s2);
void			*ft_memset(void *s, int c, size_t n);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
t_command		*ft_lstlast_cmd(t_command *lst);
t_token			*ft_lstnew_token(char *content);
int 			ft_strcmp(char *s1, char *s2);
void			ft_putstr_fd(char *s, int fd);
int 			ft_isnumber(const char *str);
t_token			*ft_lstlast(t_token *lst);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *s);
long			ft_atol(const char *str);
int				ft_lstsize(t_token *lst);
char			*ft_itoa(int n);

#endif






































// /*_______________EXEMPLE_________________________*/

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
