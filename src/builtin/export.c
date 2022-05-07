/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:47:26 by cvine             #+#    #+#             */
/*   Updated: 2022/05/06 20:30:58 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_2d_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	print_sorted_envp(t_list **envp)
{
	int		i;
	char	**envp_copy;
	char	envp_len;

	i = 0;
	envp_copy = convert_env_lst(*envp);
	envp_len = get_2d_array_len(envp_copy);
	quicksort_2d_array(envp_copy, 0, envp_len - 1);
	while (i < envp_len)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(envp_copy[i], STDOUT_FILENO);
		i++;
	}
}

void	export(char	**cmd, t_list **env_head)
{
	g_exit_status = 0;

	if (!cmd[1])
		print_sorted_envp(env_head);
	else
	{
		
	}
}
