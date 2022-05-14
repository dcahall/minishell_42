NAME			=	minishell

GNL_PATH		=	./gnl/

LIBFT_PATH		=	./libft/

PARSER_PATH		=	./src/parser/

SRC_PATH		=	./src/

UTILS_PATH		=	./src/utils/

BUILT_IN_PATH	=	./src/builtin/

EXECUTE_PATH	=	./src/execute/

SIGNALS_PATH	=	./src/signals/

HEADER_PATH		=	./includes/

LIBFT			=	libft.a

PARSER_LST		=	remove_extra_spaces.c		preparser.c					parser.c\
					create_tokens_list.c		remove_empty_quote.c		parse_dollar.c\
					create_group.c				handle_file_tokens.c		handle_command_tokens.c\
					delete_merge_tokens.c		handle_heredoc.c

UTILS_LST		=	find_env_value.c			malloc_error_free.c			add_piece_to_str.c\
					error_occured.c				file_opener.c				convert_env_to_lst.c\
					convert_env_to_char.c		init_builtin.c				arg_count.c\
					get_envp.c					realease_fd.c				quicksort_2d_array.c\
					get_2d_array_len.c			is_valid_id.c				get_builtin.c

BUILT_IN_LST	=	cd.c						echo.c						env.c\
					exit.c						pwd.c						export.c\
					unset.c

EXECUTE_LST		=	exec_bin.c					exec_builtin.c				execute.c

SRC_LST			=	minishell.c

SIGNALS_LST		=	ctrl_d.c					signal.c


ALL_SRC			=	$(addprefix $(SRC_PATH), $(SRC_LST))\
					$(addprefix $(PARSER_PATH), $(PARSER_LST))\
					$(addprefix $(UTILS_PATH), $(UTILS_LST))\
					$(addprefix $(BUILT_IN_PATH), $(BUILT_IN_LST))\
					$(addprefix $(EXECUTE_PATH), $(EXECUTE_LST))\
					$(addprefix $(SIGNALS_PATH), $(SIGNALS_LST))


ALL_OBJS		=	$(patsubst %.c, %.o, $(ALL_SRC))

CC				=	gcc -g

CFLAGS			=	-Wall -Wextra -Werror  -Iincludes

READLINE_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

RM				=	rm -f

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

$(NAME)		:	$(ALL_OBJS) $(ALL_HEADER)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -L$(LIBFT_PATH) -lft $(ALL_OBJS) -o $(NAME) $(READLINE_FLAGS)

%.o			:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean		:
	$(MAKE) clean -C $(LIBFT_PATH)
	$(RM) $(ALL_OBJS)

fclean		:	clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re			:	fclean all