/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:31:10 by cvine             #+#    #+#             */
/*   Updated: 2022/05/18 14:36:00 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	id_error(char *id, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd(ERR_UNSET, STDERR_FILENO);
	g_exit_status = EXIT_FAILURE;
}

int	is_valid_id(char *id, char *msg, int cmd)
{
	int	i;

	i = 0;
	while (id[i])
	{
		if ((cmd == UNSET && id[i] == '=' )
			|| !((id[0] >= 'A' && id[0] <= 'Z')
				|| (id[0] >= 'a' && id[0] <= 'z') || id[0] == '_'))
		{
			id_error(id, msg);
			return (1);
		}
		i++;
	}
	return (0);
}
