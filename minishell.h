/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:36 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/11/11 19:43:04 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_LINE_LEN 4096

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

typedef struct s_command	t_command;

typedef struct s_local
{
	char			*key;
	char			*value;
	struct s_local	*next;
}	t_local;

typedef struct s_shell
{
	t_local		*env;
	int			last_status;
	int			sig_type;
	t_command	*cmd_head;
}	t_shell;

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_type;

typedef struct s_token
{
	t_type			type;
	t_quote			amount;
	char			*value;
	int				heredoc_fd;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				**args;
	t_token				*elem;
	t_shell				*all;
	struct s_command	*next;
}	t_command;

typedef struct s_pipe
{
	int			prev_fd;
	int			pipefd[2];
	pid_t		last_pid;
	pid_t		pid;
	t_command	*cmd_list;
}	t_pipe;

typedef struct s_cmd_state
{
	char	*cmd;
	int		x;
	int		was_in_quotes;
	char	quote;
}	t_cmd_state;

/*_______________________________environnement____________________________*/

/*ENV*/
void		set_env_value(t_local **env, char *key, char *value);
void		unset_env_value(t_local **env, char *key);
char		*get_env_value(t_local *env, char *key);
t_local		*find_env_key(t_local *env, char *key);
t_local		*env_init(char **envp, t_shell *all);
void		print_export_var(char *var);
char		**env_to_tab(t_local *env);
void		sort_env_tab(char **tab);

/*__________________________________signal________________________________*/
void		handles_ctrl_d(char *line, t_shell all, t_command *cmd_list);
void		sigint_exec(t_shell *all, int sigint_seen);
void		restore_default_signals(void);
void		sigint_handler(int sig);
void		sigint_heredoc(int sig);
void		ignore_signals(void);
void		setup_sig(void);

/*______________________________clean utils_______________________________*/
void		print_err(const char *prefix, const char *cmd, const char *msg);
void		clean_exit(t_shell *all, t_command *cmd_list, int code);
int			error_code(const char *cmd, const char *msg, int code);
void		exit_child_with_cleanup(t_command *cmd, char **envp,
				char *path, int code);
void		print_invalid_id(char *arg, t_shell *all);
void		fatal_exit(const char *msg, int code);
int			redir_error(char *file, char *msg);
void		print_signal_message(t_shell *all);
void		free_command(t_command *cmd_list);
void		free_tokens(t_token *list);
void		free_split(char **array);
void		free_env(t_shell *all);
void		free_args(char **args);

/*_________________________________parsing________________________________*/
/*PARS*/
void		parsing(char *line, t_shell *all, t_command **cmd);
char		*check_input(char *line, t_shell **all);

/*EXPANSION*/
int			find_variable(t_local *env, int start, char **str, char *var_name);
char		*split_expansion(char *str, char *key, int start, char *key_value);
void		get_variable_name(char *str, char *var_name, int *var_len, int *x);
char		*expansion(t_local *env, int last_status, char **str, char *quote);
int			handle_exit_status(char **str, int last_status, int x);
int			find_word(int *y, int x, char *line, char **tmp);
int			handle_number_zero(char **str, int x);
int			handle_numbers(char **str, int x);
char		*clean_after_expansion(char *str);
char		*clean_after_expansion(char *str);
int			handle_pid(char **str, int x);

/*TOKENISATION*/
char		*between_quotes(char *line, int *x, t_shell **all, t_token **list);
char		*outside_quotes(char *line, int *x, t_shell **all, t_token **list);
int			handles_command(char *line, int x, t_token **list, t_shell **all);
t_token		*tokenisation(int x, char *line, t_token **list, t_shell **all);
int			handles_special_char(char *line, int x, t_token **list);
void		token_flag_off(char *cmd, int quote, t_token **list);
void		token_flag_on(char *cmd, int quote, t_token **list);

/*ERROR_HANDLING*/
int			check_ambiguous(char *line, int x, t_token **list, t_shell **all);
void		error_handling(t_shell **all, t_token **list);
int			check_special(t_command *cmd, t_shell *all);
t_token		*check_redir(t_token *list, t_shell **all);
t_token		*check_char(t_token *list, t_shell **all);
t_token		*check_pipe(t_token *list, t_shell **all);

/*SET_COMMAND*/
void		create_args(t_token *list, int token_count, int skip, char ***args);
void		create_cmd(t_token **tmp, t_token **new, t_token **start,
				t_token **end);
t_command	*set_command(t_command **cmd, t_token *list, t_shell *all);
void		fill_elements(t_token **list, t_token **elements);
void		fill_args(t_token *list, char ***args);

/*_______________________________executable_______________________________*/
/*EXEC*/
void		pipe_child(t_command *cmd, int prev_fd, int *pipefd);
int			process_heredocs_before_exec(t_command *cmd_list);
int			validate_command(t_command *cmd, t_shell *all);
void		restore_std(int saved_stdin, int saved_stdout);
void		exec_pipe(t_command *cmd_list, t_shell *all);
void		child_process(t_command *cmd, t_local *env);
char		*find_in_path(char *cmd, t_local *env);
void		run_parent(t_command *cmd, pid_t pid);
void		exec_child_or_parent(t_command *cmd);
int			is_valid_identifier(const char *key);
void		run_command(t_command *cmd);

/*BUILTINS*/
int			builtin_exit(char **args, t_shell *all, t_command *cmd_list);
int			builtin_export(char **args, t_local **env, t_shell *all);
int			exec_builtin(t_command *cmd, t_shell *all);
int			builtin_unset(char **args, t_local **env);
int			builtin_cd(char **args, t_local **env);
int			builtin_echo(char **args);
int			builtin_env(t_local *env);
int			builtin_pwd(t_shell *all);
int			is_builtin(char *cmd);

/*REDIR*/
int			handle_heredoc_and_errors(t_pipe *p, t_shell *all);
int			handle_redirections(t_command *cmd, int saved_stdin,
				int saved_stdout);
int			create_heredoc(char *limiter, t_command *cmd);
void		heredoc_exit(int write_fd, char *limiter,
				char *line, t_command *cmd);
int			check_ambiguous_redirect(char *value);
int			handle_redir_only(t_command *cmd);
int			apply_redir(t_token *redir);

/*__________________________________LIBFT_________________________________*/
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
long long	ft_strtoll(const char *nptr, int *is_long);
char		*ft_strjoin_free(char *s1, char *s2);
char		ft_strbrk(const char *s1, const char *s2);
t_local		*ft_lstnew_env(char *value, char *key);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char *s1, char const *s2);
void		*ft_memset(void *s, int c, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
t_command	*ft_lstlast_cmd(t_command *lst);
void		ft_putendl_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
int			ft_isnumber(const char *str);
int			ft_count_strings(char **arr);
int			ft_strisnum(const char *str);
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
char		*skip(void);

#endif
