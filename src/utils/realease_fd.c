/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realease_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:44:02 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/11 19:35:50 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	release_heredoc_fd(t_arg *group)
{
	int	i;

	i = 0;
	while (i < group->heredoc_fd_num)
	{
		close(group->heredoc_fd[i]);
		i++;
	}
}

void	release_fd(t_shell *shell)
{
	t_arg	*group;
	int		group_num;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!shell->group)
		return ;
	group_num = shell->group_num;
	group = shell->group;
	while (i < group_num)
	{
		if (group[i].heredoc_fd)
			release_heredoc_fd(&group[i]);
		if (group[i].out_fd != shell->std_out || group[i].out_fd != PIPE)
			close(group[i].out_fd);
		if (group[i].in_fd != shell->std_in || group[i].in_fd != PIPE)
			close(group[i].in_fd);	
		i++;
	}
}