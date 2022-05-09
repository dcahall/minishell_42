/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:04:13 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/08 13:18:59 by dcahall          ###   ########.fr       */
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
	shell->env_str = convert_env_lst(shell->env_lst);
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	init_builtin(shell);
}

static void	mini_init(t_shell *shell)
{
	shell->out_fd = shell->std_out;
	shell->group = NULL;
}

static void	minishell(t_shell *shell)
{
	int		error;
	char 	*cmd_line;

	cmd_line = readline("SHELL: "); 
	if (!cmd_line)
		ctrl_d();
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
	int i = 0;
	int	j = 0;
	while (i < shell->group_num)
	{
		printf("%d:", i);
		if (shell->group[i].limiter)
			printf("limiter - %s ", shell->group[i].limiter);
		while (shell->group[i].cmd && shell->group[i].cmd[j])
		{
			printf("%s ", shell->group[i].cmd[j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	// t_shell	shell;
	// t_arg	group[6];
	// char	*cmd0[] = {"sort", NULL};
	// char	*cmd1[] = {"uniq", "-c", NULL};
	// char	*cmd2[] = {"sort", "-r", NULL};
	// char	*cmd3[] = {"head", "-3", NULL};
	// char	*cmd4[] = {"cd", "..", NULL};  	/* change home */
	// char	*cmd5[] = {"export", NULL};

	// (void)argc;
	// (void)argv;
	// init_shell(&shell, envp);
	// g_exit_status = 0;
	// shell.group_num = 6;
	// shell.group = group;
	// shell.out_fd = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	// shell.group[0].in_fd = open("infile", O_RDONLY);
	// shell.group[0].cmd = cmd0;
	// shell.group[0].cmd_type = BINARY;
	// shell.group[1].in_fd = 0;
	// shell.group[1].cmd = cmd1;
	// shell.group[1].cmd_type = BINARY;
	// shell.group[2].in_fd = 0;
	// shell.group[2].cmd = cmd2;
	// shell.group[2].cmd_type = BINARY;
	// shell.group[3].in_fd = 0;
	// shell.group[3].cmd = cmd3;
	// shell.group[3].cmd_type = BINARY;
	// shell.group[4].in_fd = 0;
	// shell.group[4].cmd = cmd4;
	// shell.group[4].cmd_type = BUILTIN;
	// shell.group[5].in_fd = 0;
	// shell.group[5].cmd = cmd5;
	// shell.group[5].cmd_type = BUILTIN;
	// execute(&shell);
	// close(shell.group[0].in_fd);
	// close(shell.out_fd);
	t_shell	shell; 

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	// while (1)
	// {
		mini_init(&shell);
		minishell(&shell);
		// free_group(shell.group, shell.group_num);
		// shell.group = NULL;
	// }
	super_cleaner(&shell);
}
