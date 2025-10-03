# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #


NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -Iminishell/libft -Iminishell

OBJ_DIR     = obj
LIBFT_DIR   = minishell/libft
LIBFT       = $(LIBFT_DIR)/libft.a


# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #


SRCS = \
	main.c \
	env/set_up_shell_exec.c \
	env/set_up_shell_pars.c \
	executable/builtins/builtin.c \
	executable/builtins/cd.c \
	executable/builtins/echo.c \
	executable/builtins/env.c \
	executable/builtins/exit.c \
	executable/builtins/export.c \
	executable/builtins/pwd.c \
	executable/builtins/unset.c \
	executable/env_and_path/env_to_tab.c \
	executable/env_and_path/env_utils.c \
	executable/env_and_path/find_path.c \
	executable/exec/pipe.c \
	executable/exec/run_command.c \
	executable/free_errors/error.c \
	executable/free_errors/free.c \
	executable/redir/heredoc.c \
	executable/redir/redir.c \
	parsing/check_input.c \
	parsing/error_handling.c \
	parsing/expansion.c \
	parsing/parsing.c \
	parsing/set_command.c \
	parsing/tokenisation.c \
	parsing/free_error_pars/end_code.c \
	parsing/free_error_pars/free_args.c \
	parsing/free_error_pars/free_env.c \
	parsing/free_error_pars/free_tokens.c \
	parsing/free_error_pars/print_error.c \
	signal/signal_exec.c \
	signal/signal_pars.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)


# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #


all: $(LIBFT) $(NAME)
	@echo "Compilation : OK !"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "clean : done !"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "fclean : done !"

re: fclean all

.PHONY: all clean fclean re