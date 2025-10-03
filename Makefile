NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS =	src/main.c src/exec.c src/find_path.c src/env_utils.c src/builtins/cd.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c src/builtins/export.c \
		src/builtins/pwd.c src/builtins/unset.c src/pipes/pipe.c src/redir/heredoc.c src/redir/redir.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re