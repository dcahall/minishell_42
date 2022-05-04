/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:59:01 by cvine             #+#    #+#             */
/*   Updated: 2022/05/04 20:33:43 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **cmd, t_list **env_head)
{
	char	*cwd;

	(void)cmd;
	(void)env_head;
	cwd = getcwd(NULL, 0); 
	if (!cwd){
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
}