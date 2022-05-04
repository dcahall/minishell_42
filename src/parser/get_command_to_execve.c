/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_to_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:21:54 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:12:17 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	utils_malloc_for_arguments(t_arg group, int num_arg)
{
	if (num_arg)
	{
		group.cmd = (char **)malloc(sizeof(char *) * num_arg + 1);
		check_malloc_error(group.cmd);
	}
}

static void	malloc_for_arguments(t_arg *group, t_list *tokens)
{
	int	num_arg;
	int	i;

	i = 0;
	num_arg = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{	
			utils_malloc_for_arguments(group[i], num_arg);
			tokens = tokens->next;
			i++;
			num_arg = 0;
		}
		else
		{
			num_arg++;
			tokens = tokens->next;
		}
	}
	utils_malloc_for_arguments(group[i], num_arg);
}

void	get_command_argument(t_arg *group, t_list *tokens, int group_num)
{
	int	i;
	int	j;

	i = 0;
	malloc_for_arguments(group, tokens);
	while (tokens)
	{	
		j = 0;
		while (tokens && tokens->type != PIPE)
		{
			group[i].cmd[j] = ft_strdup(tokens->content);
			check_malloc_error(group[i].cmd[j])
			tokens = tokens->next;
			j++;
		}
		if (tokens)
			tokens = tokens->next;
		group[i].cmd[j] = NULL;
		i++;
	}
}
// НУЖНО ЗАПИСАТЬ АРГУМЕНТЫ В ДВУМЕРНЫЙ МАССИВ