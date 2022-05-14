/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:21:54 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/12 16:48:19 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	utils_malloc_for_arguments(t_arg *group, int arg_num)
{
	if (arg_num)
	{
		group->cmd = (char **)malloc(sizeof(char *) * (arg_num + 1));
		check_malloc_error(group->cmd);
		group->cmd[arg_num] = NULL;
	}
}

static void	malloc_for_arguments(t_arg *group, t_list *tokens, int group_num)
{
	int	arg_num;
	int	i;

	i = 0;
	arg_num = 0;
	while (tokens && i < group_num)
	{
		if (tokens->type == PIPE)
		{	
			utils_malloc_for_arguments(&group[i], arg_num);
			tokens = tokens->next;
			i++;
			arg_num = 0;
		}
		else
		{
			arg_num++;
			tokens = tokens->next;
		}
	}
	utils_malloc_for_arguments(&group[i], arg_num);
}

void	get_command_argument(t_arg *group, t_list *tokens, int group_num)
{
	int	i;
	int	j;

	i = 0;
	malloc_for_arguments(group, tokens, group_num);
	while (tokens)
	{	
		j = 0;
		while (tokens && tokens->type != PIPE)
		{
			group[i].cmd[j] = ft_strdup(tokens->content);
			check_malloc_error(group[i].cmd[j]);
			tokens = tokens->next;
			j++;
		}
		if (tokens)
			tokens = tokens->next;
		i++;
	}
}
