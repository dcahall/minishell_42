/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 11:02:54 by cvine             #+#    #+#             */
/*   Updated: 2022/05/11 16:42:58 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **cmd, t_list **env_head)
{
	t_list	*head;

	(void)cmd;
	head = *env_head;
	g_exit_status = EXIT_SUCCESS;
	while (env_head && head)
	{
		ft_putstr_fd(head->key, STDOUT_FILENO);
		ft_putendl_fd(head->content, STDOUT_FILENO);
		head = head->next;
	}
}
