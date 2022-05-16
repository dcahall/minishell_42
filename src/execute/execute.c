/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:45:36 by cvine             #+#    #+#             */
/*   Updated: 2022/05/15 19:28:58 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pipe(int *fdout, int *fdin)
{
	int	fdpipe[2];

	pipe(fdpipe);
	*fdout = fdpipe[1];
	*fdin = fdpipe[0];
}

/*
For the first group saves STDIN_FILENO to fdin;
In other group looks if there is a open infile, then saves it to fdin;
*/
static void	redirect_input(t_shell *shell, int i, int j, int *fdin)
{
	if (!i && shell->group[0].in_fd == shell->std_in)
		*fdin = dup(shell->std_in);
	if (shell->group[i].heredoc_fd && shell->group[i].heredoc_fd[j])
		*fdin = dup(shell->group[i].heredoc_fd[j]);
	else if (shell->group[i].in_fd != PIPE && shell->group[i].in_fd != shell->std_in)
		*fdin = shell->group[i].in_fd;
	dup2(*fdin, STDIN_FILENO);
	close (*fdin);
}

/*
for the last group saves corresponding fd (sdtout or outfile);
for other grops creates pipes and redirect output/input in a pipe
*/
static void	redirect_output(t_shell *shell, int i, int *fdin, int *fdout)
{
	if (i == shell->group_num - 1)
	{
		if (!shell->out_fd)
			*fdout = dup(shell->std_out);
		else
			*fdout = shell->out_fd;
	}
	else
		create_pipe(fdout, fdin);
	dup2(*fdout, STDOUT_FILENO);
	close(*fdout);
}

/* restore input/output fd defaults */
static void	restore_io_defaults(t_shell *shell)
{
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	close(shell->std_in);
	close(shell->std_out);
}

void	execute(t_shell *shell)
{
	int	i;
	int	j;
	int	fdin;
	int	fdout;

	i = 0;
	j = 0;
	while (i < shell->group_num)
	{
		signal(SIGINT, proc_signals);
		signal(SIGQUIT, proc_signals);
		if (shell->group[i].cmd)
		{
			redirect_input(shell, i, j, &fdin);
			redirect_output(shell, i, &fdin, &fdout);
			if (get_builtin(shell->group[i].cmd, shell->builtin))
				exec_builtin(shell, shell->group[i].cmd);
			else
				exec_bin(shell, shell->group[i].cmd);
		}
		if (shell->group[i].heredoc_fd && shell->group[i].heredoc_fd[j])
			j++;
		else
			i++;
	}
	restore_io_defaults(shell);
}
