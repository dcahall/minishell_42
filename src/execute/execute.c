/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:45:36 by cvine             #+#    #+#             */
/*   Updated: 2022/05/18 20:33:56 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_default_fd(t_shell *shell)
{
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	close(shell->std_in);
	close(shell->std_out);
}

static void	execute_cmd(t_shell *shell, char **cmd)
{
	if (get_builtin(cmd, shell->builtin))
		exec_builtin(shell, cmd);
	else
		exec_bin(shell, cmd);
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
		redir_in(shell, shell->group[i], &fdin, j);
		redir_out(shell->group[i], &fdin, &fdout);
		if (shell->group[i].in_fd != -1 && g_exit_status != EXIT_CMD_NOT_FOUND)
			execute_cmd(shell, shell->group[i].cmd);
		if (shell->group[i].heredoc_fd && shell->group[i].heredoc_fd[j])
			j++;
		else
		{
			j = 0;
			i++;
		}
	}
	restore_default_fd(shell);
}
