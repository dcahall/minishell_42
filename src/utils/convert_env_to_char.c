/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 11:57:19 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/01 15:08:41 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_list_str(t_list *node)
{
	char	*final_str;

	final_str = NULL;
	if (!node->content)
	{
		if (node->key)
			final_str = ft_strdup(node->key);
	}
	else
		final_str = ft_strjoin(node->key, node->content);
	check_malloc_error(final_str);
	return (final_str);
}

char **convert_env_lst(t_list *env_lst)
{
	char	**env;
	int		i;

	if (!env_lst)
		return (NULL);
	i = 0;
	env = (char **)malloc(sizeof(char *) * (ft_lstsize(env_lst) + 1));
	check_malloc_error(env);
	while (env_lst)
	{
		env[i] = get_list_str(env_lst);
		env_lst = env_lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

