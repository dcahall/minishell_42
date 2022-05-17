/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:45:36 by cvine             #+#    #+#             */
/*   Updated: 2022/05/16 18:29:31 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_to_pipe(int *fdout, int *fdin)
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
static void	redir_in(t_shell *shell, int i, int j, int *fdin)
{
	if (!i && shell->group[0].in_fd == shell->std_in)
		*fdin = dup(shell->std_in);
	if (shell->group[i].heredoc_fd && shell->group[i].heredoc_fd[j])
		*fdin = dup(shell->group[i].heredoc_fd[j]);
	else if (shell->group[i].in_fd != PIPE
			&& shell->group[i].in_fd != shell->std_in)
		*fdin = shell->group[i].in_fd;
	dup2(*fdin, STDIN_FILENO);
	close (*fdin);
}

/*
for the last group saves corresponding fd (sdtout or outfile);
for other grops creates pipes and redir output/input in a pipe
*/
static void	redir_out(t_shell *shell, int i, int *fdin, int *fdout)
{
	if (i != shell->group_num - 1)
		redir_to_pipe(fdout, fdin);
	else
		*fdout = shell->out_fd;
	dup2(*fdout, STDOUT_FILENO);
	close(*fdout);
}

/* restore input/output fd defaults */
static void	restore_default_fd(t_shell *shell)
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
		proc_signals();
		if (shell->group[i].cmd)
		{
			redir_in(shell, i, j, &fdin);
			redir_out(shell, i, &fdin, &fdout);
			if (get_builtin(shell->group[i].cmd, shell->builtin))
				exec_builtin(shell, shell->group[i].cmd);
			else
				exec_bin(shell, shell->group[i].cmd);
		}
		if (shell->group[i].heredoc_fd && &shell->group[i].heredoc_fd[j]
			&& g_exit_status != EXIT_CMD_NOT_FOUND)
			j++;
		else
			i++;
	}
	restore_default_fd(shell);
}
