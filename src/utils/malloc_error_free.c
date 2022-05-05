/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:34:46 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/05 16:26:28 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_malloc_error(void *ptr)
{
	if (!ptr)
		exit(EXIT_FAILURE);
}

void	try_free(void *content)
{
	if (content)
		free(content);
}

void	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_group(t_arg *group, int group_num)
{
	int	i;

	i = 0;
	if (!group)
		return ;
	while (i < group_num)
	{
		if (group[i].limiter)
			free(group[i].limiter);
		if (group[i].cmd)
			free_str_array(group[i].cmd);
		i++;
	}
	free(group);
}

void	super_cleaner(t_shell *shell)
{
	if (shell->group)
		free_group(shell->group, shell->group_num);
	if (shell->env_lst)
		ft_lstclear(&shell->env_lst, free);
	if (shell->env_str)
		free_str_array(shell->env_str);
	close(shell->std_in);
	close(shell->std_out);
}