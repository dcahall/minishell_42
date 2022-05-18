/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:45:36 by cvine             #+#    #+#             */
/*   Updated: 2022/05/18 17:12:57 by dcahall          ###   ########.fr       */
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
		if (shell->group[i].cmd)
		{
			if (redir_in(shell, shell->group[i], &fdin, j) == EXIT_SUCCESS)
			{
				redir_out(shell->group[i], &fdin, &fdout);
				execute_cmd(shell, shell->group[i].cmd);
			}
			i++;
			continue ;
		}
		if (shell->group[i].heredoc_fd && shell->group[i].heredoc_fd[j]
			&& g_exit_status != EXIT_CMD_NOT_FOUND)
			j++;
		else
			i++;
	}
	restore_default_fd(shell);
}
