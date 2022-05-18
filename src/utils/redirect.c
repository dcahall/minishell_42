/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:21 by cvine             #+#    #+#             */
/*   Updated: 2022/05/18 17:13:02 by dcahall          ###   ########.fr       */
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

void	redir_out(t_arg group, int *fdin, int *fdout)
{
	if (group.out_fd == PIPE)
		redir_to_pipe(fdout, fdin);
	else
		*fdout = group.out_fd;
	dup2(*fdout, STDOUT_FILENO);
	close(*fdout);
}

int	redir_in(t_shell *shell, t_arg group, int *fdin, int j)
{
	if (group.in_fd == -1)
		return (EXIT_FAILURE);
	if (group.heredoc_fd && group.heredoc_fd[j])
		*fdin = dup(group.heredoc_fd[j]);
	else if (group.in_fd != PIPE && group.in_fd != shell->std_in)
		*fdin = group.in_fd;
	dup2(*fdin, STDIN_FILENO);
	close(*fdin);
	return (EXIT_SUCCESS);
}
