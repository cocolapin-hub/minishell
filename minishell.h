#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_LINE_LEN 4096
#define SKIP_TOKEN ((char *)1)

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdint.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
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

typedef struct s_command t_command;

typedef struct s_shell {
    t_local           		*env;     		// VAR || $HOME ETC
    int						last_status;   	// Word or PATH
	int						sig_type;
	t_command				*cmd_head;
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

typedef struct s_cmd_state
{
	char	*cmd;
	int		x;
	int		was_in_quotes;
	char	quote;
}	t_cmd_state;


/*_______________________________environnement_______________________________*/
/*PARS*/ //--> on garde celui ci
void		setup_shell(t_shell *all, char **envp);

/*EXEC*/
//t_local			*env_init(char **envp);

/*ENV*/ //--> pour les fonction en rapport avec env
void    	set_env_value(t_local **env, char *key, char *value);
void   		unset_env_value(t_local **env, char *key);
char		*get_env_value(t_local *env, char *key);
t_local		*find_env_key(t_local *env, char *key);
void		print_export_var(char *var);
char		**env_to_tab(t_local *env);
void		sort_env_tab(char **tab);



/*__________________________________signal__________________________________*/
void		handles_ctrl_d(char *line, t_shell all, t_command *cmd_list);
int 		handles_ctrl_c(t_shell all, char *line);
void 		setup_heredoc_signals(void);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);
void		sigint_heredoc(int sig);

void		setup_sig(void);



/*_________________________________parsing_________________________________*/
/*PARS*/
void		parsing(char *line, t_shell *all, t_command **cmd);
char		*check_input(char *line, t_shell **all);

/*EXPANSION*/
int			find_variable_in_env(t_local *env, int start, char **str, char *var_name);
char 		*split_for_expansion(char *str, char *key, int start, char *key_value);
void		get_variable_name(char *str, char *var_name, int *var_len, int *x);
char 		*expansion(t_local *env, int last_status, char *str, char *quote);
int 		handle_exit_status(char **str, int last_status, int x);
int			handle_number_zero(char **str, int x);
int			handle_numbers(char **str, int x);
char 		*clean_after_expansion(char *str);
int 		handle_pid(char **str, int x);

/*TOKENISATION*/
char		*between_quotes(char *line, int *x, t_shell **all, t_token **list);
char		*outside_quotes(char *line, int *x, t_shell **all, t_token **list);
int 		handles_command(char *line, int x, t_token **list, t_shell **all);
t_token		*tokenisation(char *line, t_token **list, t_shell **all);
int			handles_special_char(char *line, int x, t_token **list);

/*ERROR_HANDLING*/
t_token		*check_first_word(t_token *list, t_shell **all);
void 		error_handling(t_shell **all, t_token **list);
t_token 	*check_redir(t_token *list, t_shell **all);
t_token 	*check_char(t_token *list, t_shell **all);
t_token 	*check_pipe(t_token *list, t_shell **all);

/*SET_COMMAND*/
void		create_args(t_token *list, int token_count, int skip_next, char ***args);
void		create_cmd(t_token **tmp, t_token **new, t_token **start, t_token **end);
t_command	*set_command(t_command **cmd, t_token *list, t_shell *all);
void		fill_elements(t_token **list, t_token **elements);
void		fill_args(t_token *list, char ***args);

/*FREE & ERROR*/
void		print_error(char *line, char *msg);
void		free_tokens(t_token *list);
void		end_code(t_command *cmd);
void		free_args(char **args);




/*________________________________executable________________________________*/
/*EXEC*/
void		exec_pipe(t_command *cmd_list, t_shell *all);
void		child_process(t_command *cmd, t_local *env);
char		*find_in_path(char *cmd, t_local *env);
int			is_valid_identifier(const char *key);
void		run_command(t_command *cmd);

/*BUILTINS*/
int 		builtin_exit(char **args, t_shell *all, t_command *cmd_list);
int			exec_builtin(t_command *cmd, t_shell *all);
int			builtin_export(char **args, t_local **env, t_shell *all);
int			builtin_unset(char **args, t_local **env);
int			builtin_cd(char **args, t_local **env);
int			builtin_echo(char **args);
int			builtin_env(t_local *env);
int			builtin_pwd(t_shell *all);
int			is_builtin(char *cmd);

/*REDIR*/
int			create_heredoc(char *limiter, t_shell *all);
int			apply_redir(t_token *redir, t_shell *all);

/*ERROR & FREE*/
void		exit_clean_af(t_shell *all, t_command *cmd_list, int code);
int			exec_error(const char *cmd, const char *msg, int code);
void		fatal_error(const char *msg, int code);
void		print_error_exec(char *cmd, char *msg);
void		print_invalid_identifier(char *arg, t_shell *all);
int			redir_error(char *file, char *msg);
void		free_command(t_command *cmd);
void		free_split(char **array);



/*_________________________________exit_________________________________*/
void		free_env(t_shell *all);



/*________________________________LIBFT________________________________*/
t_command	*ft_lstnew_cmd(char **args, t_token *elements, t_shell *all);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		ft_lstadd_back_cmd(t_command **lst, t_command *new);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_islonglong(const char *str, long long *out);
int			ft_strstr(const char *big, const char *little);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_lstadd_back(t_token **lst, t_token *new);
char		*ft_strdup_m(const char *s, int x, int len);
t_token		*ft_lstnew_token(char *content, char quote);
long long 	ft_strtoll(const char *nptr, int *is_long);
char		ft_strbrk(const char *s1, const char *s2);
t_local		*ft_lstnew_env(char *value, char *key);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char *s1, char const *s2);
void		*ft_memset(void *s, int c, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
t_command	*ft_lstlast_cmd(t_command *lst);
void		ft_putendl_fd(char *s, int fd);
int 		ft_strcmp(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
int 		ft_isnumber(const char *str);
int 		ft_count_strings(char **arr);
int 		ft_strisnum(const char *str);
int			ft_atoi(const char *nptr);
t_token		*ft_lstlast(t_token *lst);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
long		ft_atol(const char *str);
int			ft_lstsize(t_token *lst);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*ft_itoa(int n);


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
