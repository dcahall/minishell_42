/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:57:50 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:12:28 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*malloc_for_arguments(t_list group, t_list *tokens)
{
	int	num_arg
}

void get_command_argument(t_arg *group, t_list *tokens, int group_num)
{
	t_list	*runner;
	int		i;

	i = 0;
	runner = tokens;
	while (i < group_num)
	{
		runner = malloc_for_arguments(group[i], runner);
		i++;
	}
}
