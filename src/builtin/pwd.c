/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:59:01 by cvine             #+#    #+#             */
/*   Updated: 2022/05/07 11:03:28 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **cmd, t_list **env_head)
{
	char	*cwd;

	(void)cmd;
	(void)env_head;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		g_exit_status = EXIT_SUCCESS;
	}
	else
		g_exit_status = EXIT_FAILURE;
}
