/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:04:13 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:37:19 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Нужно сделать обработку ошибок препарсинга и парсинга
** после написания парсинга и препарсинга
*/

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env_lst = convert_list_char(envp);
	shell->env_str = conver_env_lst(shell->env_lst);
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	// init_builtin(shell);
}

static void	minishell(t_shell *shell)
{
	int		error;
	char 	*cmd_line;
	// t_list	*tokens;
	(void)shell;
	cmd_line = readline("SHELL: ");
	error = preparser(cmd_line);
	if (error == 2 || error == 1)
	{
		if (error == 2)
		{
			try_free(cmd_line);
			error_occured("parser", SYNTAX_ERROR);
		}
		return ;
	}
	if (parser(cmd_line, shell) == EXIT_FAILURE)
	{
		super_cleaner(shell);
		return ;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell; 
	init_shell(&shell, envp);
	(void)argc;
	(void)argv;
	// while (1)
		minishell(&shell);
	super_cleaner(&shell);
	close(shell.std_in);
	close(shell.std_out);
}