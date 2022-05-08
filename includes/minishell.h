/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:29:23 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/08 13:12:18 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "error_occured.h"
# include "readline/readline.h"
# include "readline/history.h"
# define BINARY				-1
# define PIPE				-1
# define WORD				0
# define REDIRECT_OUT		1
# define REDIRECT_IN		2
# define DOUBLE_REDIRECT	3
# define SINGLE_QUOTE		5
# define DOUBLE_QUOTE		6
# define EMPTY				7
# define HERE_DOC			9
# define NUM_OF_BUILTIN		10
# define BUILTIN			11
# define OUT_OF_RANGE		255

int	g_exit_status;

typedef void	(*t_func_ptr)(char **cmd, t_list **env_head);
typedef			t_func_ptr	t_builtin_func;

typedef struct s_builtin
{
	const char		*name;
	t_builtin_func	func_ptr;
}	t_builtin;

typedef struct s_arg
{
	int		in_fd;
	int		out_fd;
	char	*limiter;
	int		cmd_type;
	char	**cmd;
}	t_arg;

typedef struct s_shell
{
	int		std_out; 						/* DEFAULT STDOUT FD */
	int		std_in;							/* DEFAULT STDIN FD */
	int		out_fd;							/* OUTFILE IN THE LAST GROUP */
	int		group_num;						/* number of groups */
	t_arg	*group;							/* list of groups */
	t_list	*env_lst;						/* list representation of envp */
	char	**env_str;						/* copy of envp */
	t_builtin	builtin[NUM_OF_BUILTIN];	/* list of builtins */
}	t_shell;


/*
** Presort looks for closing quotes,
** a pipe at the end or beginning of a line.
** It also removes extra spaces and empty quotes.
*/
int		preparser(char *cmd_line);
int		is_empty_quote(char *str, int i);
int		check_empty_string(const char *cmd_line, int *i);


/*
** Splits a string into token sheets
** Reveals what is in parentheses
*/
int		word_or_symbol(char *cmd_line, int i, t_list *token);
int		quote(char *cmd_line, int i, t_list *token);
char	*parse_dollar(char *cmd_line, t_shell *shell);
t_list	*create_token_list(char *cmd_line);
void	merge_tokens(t_list **tokens);
void	delete_empty_tokens(t_list **tokens);
void	delete_file_tokens(t_list **tokens);

int		parser(char *cmd_line, t_shell *shell);
int		create_group(t_shell *shell, t_list **tokens);
int		handle_all_file(t_shell *shell, t_list **tokens, t_arg *l_group);
void	get_command_argument(t_arg *group, t_list *tokens, int group_num);
char	*remove_extra_spaces(char *str, int start, int end);
char	*remove_empty_quote(char *str);
void	skip_quote(char *str, int *start);



/*
**	Utils
*/
char	*find_env(char **envp, char *str, int start);
char	*add_piece_to_str(char *add, char *str, int start, int end);
int		end_path_name(char *str, int start);
int		len_env_key(char *str);

t_list	*convert_list_char(char **envp);
char	**convert_env_lst(t_list *env_lst);
void	add_new_env(t_list **envp, char *new_env);
void	del_env_param(t_list **envp, char *key);

void	free_str_array(char **array);
void	try_free(void *content);
void	check_malloc_error(void *ptr);
void	super_cleaner(t_shell *shell);
void	free_group(t_arg *group, int group_num);
void	release_fd(t_shell *shell);

void	error_occured(const char *the_reason, char *error_message);

int		open_file(char *file, int occasion);

void			init_builtin(t_shell *shell);
int				arg_count(char	**cmd);
char			*get_envp_value(t_list *env_head, char *var);
t_list			*get_envp(t_list *env_head, char *var);
t_builtin_func	get_builtin(char	**cmd, t_builtin *builtin);
void			quicksort_2d_array(char **array, int left, int right);
int				get_2d_array_len(char **array);

/* EXECUTE */

void			execute(t_shell *shell);
void			exec_bin(t_shell *shell, char **cmd);
void			exec_builtin(t_shell *shell, char **cmd);
/* BUILTIN */

void			cd(char **cmd, t_list **envp);
void			pwd(char **cmd, t_list **env_head);
void			echo(char **cmd, t_list **env_head);
void			env(char **cmd, t_list **env_head);
void			ft_exit(char **cmd, t_list **env_head);
void			export(char	**cmd, t_list **env_head);
void			unset(char **cmd, t_list **env_head);

/* SIGNALS */

int ctrl_d(void);

# endif 
