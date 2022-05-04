/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realease_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:44:02 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:13:56 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	release_fd(t_shell *shell)
{
	t_arg	*group;
	int		group_num;
	int		i;

	i = 0;
	group_num = shell->group_num;
	group = shell->group;
	while (i < group_num)
	{
		if (group[i].out_fd != shell->std_out || group[i].out_fd != PIPE)
			close(group[i].out_fd);
		if (group[i].in_fd != shell->std_in || group[i].in_fd != PIPE)
			close(group[i].in_fd);	
		i++;
	}
}