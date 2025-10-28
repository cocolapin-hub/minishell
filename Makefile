# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #


NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -Iminishell

OBJ_DIR     = obj


# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #


SRCS = \
	main.c \
	env/setup_shell_pars.c \
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
	executable/env_and_path/set_env_value.c \
	executable/exec/exec_pipe.c \
	executable/exec/run_command.c \
	executable/free_errors/error.c \
	executable/free_errors/free.c \
	executable/redir/heredoc.c \
	executable/redir/redir.c \
	executable/exec/child_process.c \
	executable/exec/pipe_child.c \
	parsing/parsing.c \
	parsing/check_input.c \
	parsing/set_cmd/fill_elements.c \
	parsing/set_cmd/set_command.c \
	parsing/set_cmd/create_args.c \
	parsing/set_cmd/create_cmd.c \
	parsing/set_cmd/fill_args.c \
	parsing/free_error_pars/end_code.c \
	parsing/free_error_pars/free_args.c \
	parsing/free_error_pars/free_env.c \
	parsing/free_error_pars/free_tokens.c \
	parsing/free_error_pars/print_error.c \
	parsing/set_token/handles_special_char.c \
	parsing/set_token/handles_command.c \
	parsing/set_token/outside_quotes.c \
	parsing/set_token/between_quotes.c \
	parsing/set_token/tokenisation.c \
	parsing/set_token/expansion/find_variable_in_env.c \
	parsing/set_token/expansion/split_for_expansion.c \
	parsing/set_token/expansion/handle_exit_status.c \
	parsing/set_token/expansion/handle_number_zero.c \
	parsing/set_token/expansion/get_variable_name.c \
	parsing/set_token/expansion/handle_numbers.c \
	parsing/set_token/expansion/handle_pid.c \
	parsing/set_token/expansion/expansion.c \
	parsing/syntax/check_first_word.c \
	parsing/syntax/error_handling.c \
	parsing/syntax/check_redir.c \
	parsing/syntax/check_char.c \
	parsing/syntax/check_pipe.c \
	signal/signal_exec.c \
	signal/ctrl_c.c\
	signal/ctrl_d.c\
	signal/signal_utils.c \
	libft/ft_islonglong.c \
	libft/ft_strtoll.c \
	libft/ft_strisnum.c \
	libft/ft_strbrk.c \
	libft/ft_atol.c \
	libft/ft_isnumber.c \
	libft/ft_isalpha.c \
	libft/ft_isalnum.c \
	libft/ft_isdigit.c \
	libft/ft_itoa.c \
	libft/ft_lstadd_back_cmd.c \
	libft/ft_lstadd_back.c \
	libft/ft_lstlast_cmd.c \
	libft/ft_lstlast.c \
	libft/ft_lstnew_cmd.c \
	libft/ft_lstnew_env.c \
	libft/ft_lstnew_token.c \
	libft/ft_lstsize.c \
	libft/ft_memcpy.c \
	libft/ft_atoi.c \
	libft/ft_putstr_fd.c \
	libft/ft_putendl_fd.c \
	libft/ft_count_strings.c \
	libft/ft_split.c \
	libft/ft_strchr.c \
	libft/ft_strcmp.c \
	libft/ft_strcpy.c \
	libft/ft_strdup_m.c \
	libft/ft_strdup.c \
	libft/ft_strjoin.c \
	libft/ft_strlen.c \
	libft/ft_substr.c \
	libft/ft_strstr.c \
	libft/ft_calloc.c \
	libft/ft_strlcpy.c \
	libft/ft_memset.c \
	libft/ft_strtrim.c \
	libft/ft_strjoin_free.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)


# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #


all: $(NAME)
	@echo "Compilation : OK !"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "clean : done !"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean : done !"

re: fclean all

.PHONY: all clean fclean re
