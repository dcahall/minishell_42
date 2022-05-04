/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:37:55 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:31:42 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, char *var)
{
	while (ft_strncmp(*envp, var, 5) && *envp)
		(*envp)++;
	return (*envp + 5);
}

// char	*env(t_list *env_head, char *var)
// {
// 	while (env_head)
// 	{
// 		if (!ft_strcmp(env_head->key, var))
// 			return (env_head->content);
// 		env_head = env_head->next;
// 	}
// 	return (NULL);
// }
