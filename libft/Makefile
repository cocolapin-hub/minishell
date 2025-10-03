NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = \
	ft_atol.c \
	ft_isnumber.c \
	ft_itoa.c \
	ft_lstadd_back_cmd.c \
	ft_lstadd_back.c \
	ft_lstlast_cmd.c \
	ft_lstlast.c \
	ft_lstnew_cmd.c \
	ft_lstnew_env.c \
	ft_lstnew_token.c \
	ft_lstsize.c \
	ft_memcpy.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdup_m.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlen.c \
	ft_strstr.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
