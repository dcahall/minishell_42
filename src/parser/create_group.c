/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:11:59 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:12:08 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	num_group(t_list *tokens)
{
	int		count;

	count = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static void	init_group_shell(t_shell *shell, t_arg *group, int group_num)
{
	int	i;

	i = 0;
	shell->group_num = group_num;
	shell->group = group;
	while (i < group_num)
	{
		group[i].limiter = NULL;
		group[i].cmd = NULL;
		group[i].in_fd = shell->std_in;
		group[i].out_fd = shell->std_out;
		i++;
	}
}

static int	check_empty_group(t_arg *group, int num_group)
{
	int	i;

	i = 0;
	while (i < num_group)
	{
		if (group[i].cmd == NULL)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_group(t_shell *shell, t_list *tokens)
{
	t_arg	*group;
	int		group_num;

	group_num = num_group(tokens);
	group = (t_arg *)malloc(sizeof(t_arg) * group_num);
	check_malloc_error(group);
	init_group_shell(shell, group, group_num);
	merge_tokens(&tokens);
	delete_empty_tokens(&tokens);
	if (handle_all_file(shell, &tokens, group) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	delete_file_tokens(&tokens);
	if (!tokens)
		return (EXIT_FAILURE);
	get_command_argument(shell->group, tokens, group_num);
	return (check_empty_group(group, group_num));
}
