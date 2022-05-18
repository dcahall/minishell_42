/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:04:13 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/18 19:38:20 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env_lst = convert_list_char(envp);
	shell->env_str = convert_env_lst(shell->env_lst);
	init_builtin(shell);
}

static void	mini_init(t_shell *shell)
{
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	shell->group = NULL;
}

static void	minishell(t_shell *shell)
{
	int		error;
	char	*cmd_line;

	cmd_line = readline("SHELL: ");
	if (!cmd_line)
		ctrl_d();
	if (*cmd_line)
		add_history(cmd_line);
	error = preparser(cmd_line);
	if (error == 2 || error == 1)
	{
		if (error == 2)
			error_occured("parser", SYNTAX_ERROR);
		try_free(cmd_line);
		return ;
	}
	if (parser(cmd_line, shell) == EXIT_FAILURE)
		return ;
	execute(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		prompt_signals();
		mini_init(&shell);
		minishell(&shell);
		release_fd(&shell);
		free_group(shell.group, shell.group_num);
		shell.group = NULL;
	}
}
