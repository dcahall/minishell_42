/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 11:02:54 by cvine             #+#    #+#             */
/*   Updated: 2022/05/07 11:02:56 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **cmd, t_list **env_head)
{
	t_list	*head;

	(void)cmd;
	head = *env_head;
	while (env_head && head->content)
	{
		printf("%s%s\n", head->key, head->content);
		head = head->next;
	}
}
