/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:36:04 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 20:17:07 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_path_name(char *str, int start)
{
	while (ft_isspace(str[start]) == 0 && str[start] && str[start] != '$'
		&& str[start] != '"')
		start++;
	return (start);
}

int	len_env_key(char *str)
{
	int	i;
	
	i = 0;
	while (str && str[i] != '=' && str[i])
		i++;
	return (i);
}

char	*find_env(char **envp, char *str, int start)
{
	char	*env_name;
	char	*env_value;
	int		len_env;
	int		end;
	int		i;

	i = 0;
	end = end_path_name(str, start);
	env_name = ft_substr(str, start, end - start);
	check_malloc_error(env_name);
	while (envp[i])
	{
		len_env = len_env_key(envp[i]);
		if (ft_strncmp(envp[i], env_name, len_env) == 0)
		{
			env_value = ft_strdup(envp[i]);
			check_malloc_error(env_value);
			free(env_name);
			return (env_value);
		}
		i++;
	}
	free(env_name);
	return (NULL);
}