/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:04:13 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/17 13:58:47 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Нужно сделать обработку ошибок препарсинга и парсинга
** после написания парсинга и препарсинга*/

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
	// shell->out_fd = shell->std_out;
	shell->group = NULL;
}

static void	minishell(t_shell *shell)
{
	int		error;
	char 	*cmd_line;

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
	// int i = 0;
	// int	j = 0;
	// int	k = 0;
	// while (i < shell->group_num)
	// {
	// 	printf("%d:", i);
	// 	while (shell->group[i].cmd && shell->group[i].cmd[j])
	// 	{
	// 		printf("%s ", shell->group[i].cmd[j]);
	// 		j++;
	// 	}
	// 	if (shell->group[i].heredoc_fd)
	// 	{
	// 		printf("in_heredoc_fd = ");
	// 		while (k < shell->group[i].heredoc_fd_num)
	// 		{
	// 			printf("%d ", shell->group[i].heredoc_fd[k]);
	// 			k++;
	// 		}
	// 	}
	// 	else
	// 		printf("in_fd = %d", shell->group[i].in_fd);
	// 	printf("out_fd = %d", shell->group[i].out_fd);
	// 	printf("\n");
	// 	j = 0;
	// 	i++;
	// }
}

int main(int argc, char **argv, char **envp)
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
