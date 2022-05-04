/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:29:23 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:32:40 by dcahall          ###   ########.fr       */
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
# define CD					0
# define PWD				1
# define ENV				2
# define ECHO				3
# define EXIT				4
# define UNSET				5
# define EXPORT 			6
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
	char	*limiter;
	int		cmd_type;
	char	**cmd;
}	t_arg;

/*
** Убрать out_fd оставь один out_fd в структуре shell
** ПЕРЕПИСАТЬ НАХУЙ OUT_FD
*/

typedef struct s_shell
{
	int		std_out; 
	int		std_in;
	int		out_fd;
	int		group_num;
	t_arg	*group;
	t_list	*env_lst;
	char	**env_str;
	t_builtin	builtin[NUM_OF_BUILTIN];
}	t_shell;


/*
** Presort looks for closing quotes,
** a pipe at the end or beginning of a line.
** It also removes extra spaces and empty quotes.
*/
int		preparser(char *cmd_line);
char	*remove_extra_spaces(char *str, int start, int end);
char	*remove_empty_quote(char *str);
int		is_empty_quote(char *str, int i);


/*
** Splits a string into token sheets
** Reveals what is in parentheses
*/
int		word_or_symbol(char *cmd_line, int i, t_list *token);
int		quote(char *cmd_line, int i, t_list *token);
char	*parse_dollar(char *cmd_line, t_shell *shell);


void	skip_quote(char *str, int *i);
int		parser(char *cmd_line, t_shell *shell);
int		create_group(t_shell *shell, t_list *tokens);
int		handle_all_file(t_shell *shell, t_list **tokens, t_arg *l_group);
void	delete_used_tokens(t_list **tokens);


/*
**	Utils
*/
char	*find_env(char **envp, char *str, int start);
char	*add_piece_to_str(char *add, char *str, int start, int end);
int		end_path_name(char *str, int start);
int		len_env_key(char *str);

t_list	*convert_list_char(char **envp);
char	**conver_env_lst(t_list *env_lst);
void	add_new_env(t_list **envp, char *new_env);
void	del_env_param(t_list **envp, char *key);

void	free_str_array(char **array);
void	try_free(void *content);
void	check_malloc_error(void *ptr);
void	super_cleaner(t_shell *shell);

void	error_occured(const char *the_reason, char *error_message);

int		open_file(char *file, int occasion);

void	init_builtin(t_shell *shell);
int		arg_count(char	**cmd);
char	*get_env_value(char **envp, char *var);
// char			*get_env_value(t_list *env_head, char *var);
t_builtin_func	get_builtin(char	**cmd, t_builtin *builtin);

/* EXECUTE */

void	execute(t_shell *shell);
void	exec_bin(t_shell *shell, char **cmd);
void	exec_builtin(t_shell *shell, char **cmd);

/* BUILTIN */

void	pwd(char **cmd, t_list **env_head);
void	echo(char **cmd, t_list **env_head);
void	env(char **cmd, t_list **env_head);
void	ft_exit(char **cmd, t_list **env_head);

# endif 
