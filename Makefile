NAME    = minishell

SRCS    = 	main.c \
			parsing/print_error.c \
			parsing/check_input.c \
			parsing/parsing.c \



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
