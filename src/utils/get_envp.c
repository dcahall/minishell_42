/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:37:55 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/05 15:33:22 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envp_value(t_list *env_head, char *var)
{
	while (env_head)
	{
		if (!ft_strcmp(env_head->key, var))
			return (env_head->content);
		env_head = env_head->next;
	}
	return (NULL);
}

t_list	*get_envp(t_list *env_head, char *var)
{
	while (env_head)
	{
		if (!ft_strcmp(env_head->key, var))
			return (env_head);
		env_head = env_head->next;
	}
	return (NULL);
}