NAME    = minishell

SRCS    = 	main.c \
			parsing/error_handling.c \
			parsing/tokenisation.c \
			parsing/check_input.c \
			parsing/set_command.c \
			parsing/expansion.c \
			parsing/parsing.c \
			fonctions/ft_lstadd_back_cmd.c \
			fonctions/ft_lstnew_token.c \
			fonctions/ft_lstadd_back.c \
			fonctions/ft_lstlast_cmd.c \
			fonctions/ft_lstnew_env.c \
			fonctions/ft_lstnew_cmd.c \
			fonctions/print_error.c \
			fonctions/free_tokens.c \
			fonctions/ft_strdup_m.c \
			fonctions/ft_lstlast.c \
			fonctions/ft_strjoin.c \
			fonctions/ft_lstsize.c \
			fonctions/ft_strstr.c \
			fonctions/ft_strdup.c \
			fonctions/ft_strlen.c \
			fonctions/ft_itoa.c \
			setup/setup_signal.c \
			setup/setup_shell.c \





CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
