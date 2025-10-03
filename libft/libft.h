
#ifndef LIBFT_H
# define LIBFT_H

# include "../minishell.h"

/*___________LIBFT___________*/
t_command		*ft_lstnew_cmd(char **args, t_token *elements, t_shell *all);
void			ft_lstadd_back_cmd(t_command **lst, t_command *new);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_strstr(const char *big, const char *little);
void			ft_lstadd_back(t_token **lst, t_token *new);
char			*ft_strdup_m(const char *s, int x, int len);
t_local			*ft_lstnew_env(char *value, char *key);
char			*ft_strjoin(char *s1, char const *s2);
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



/*_____RESERVE_____*/
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// char		*ft_strnstr(const char *big, const char *little, size_t len);
// char		*ft_substr(char const *s, unsigned int start, size_t len);
// char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// void		ft_striteri(char *s, void (*f)(unsigned int, char *));
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// void		*ft_memmove(void *dst, const void *src, size_t len);
// int		ft_memcmp(const void *s1, const void *s2, size_t n);
// void		ft_lstdelone(t_list	*lst, void (*del)(void *));
// void		ft_lstclear(t_list **lst, void (*del)(void *));
// char		*ft_strtrim(char const *s1, char const *set);
// void		*ft_memchr(const void *s, int c, size_t n);
// void		ft_lstiter(t_list *lst, void (*f)(void *));
// void		ft_lstadd_front(t_list **lst, t_list *new);
// void		ft_lstadd_back(t_list **lst, t_list *new);
// void		*ft_memset(void *b, int c, size_t len);
// void		*ft_calloc(size_t count, size_t size);
// char		*ft_strrchr(const char *s, int c);
// char		*ft_strcpy(char *s1, char *s2);
// void		ft_putendl_fd(char *s, int fd);
// void		ft_putchar_fd(char c, int fd);
// void		ft_bzero(void *s, size_t n);
// void		ft_putnbr_fd(int n, int fd);
// t_list	*ft_lstnew(void *content);
// int		ft_atoi(const char *str);
// t_list	*ft_lstlast(t_list *lst);
// int		ft_lstsize(t_list *lst);
// char		*get_next_line(int fd);
// int		ft_toupper(int c);
// int		ft_tolower(int c);
// int		ft_isalpha(int c);
// int		ft_isdigit(int c);
// int		ft_isalnum(int c);
// int		ft_isascii(int c);
// int		ft_isprint(int c);
// char		*ft_itoa(int n);