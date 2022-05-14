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
		group[i].heredoc_fd = NULL;
		group[i].cmd = NULL;
		group[i].in_fd = shell->std_in;
		group[i].out_fd = shell->std_out;
		i++;
	}
}

static void	command_to_lowercase(t_arg	*group, int	group_num)
{
	int	i;

	i = 0;
	while (i < group_num)
	{
		if (group->cmd && group->cmd[0])
			str_tolower(&group->cmd[0]);
		i++;
	}
}

void	create_group(t_shell *shell, t_list **tokens)
{
	t_arg	*group;
	int		group_num;

	group_num = num_group(*tokens);
	group = (t_arg *)malloc(sizeof(t_arg) * group_num);
	check_malloc_error(group);
	init_group_shell(shell, group, group_num);
	merge_tokens(tokens);
	delete_empty_tokens(tokens);
	handle_heredoc(shell, tokens);
	if (!*tokens)
		return ;
	handle_all_file(shell, tokens, group);
	delete_file_tokens(tokens);
	if (!*tokens)
		return ;
	get_command_argument(shell->group, *tokens, group_num);
	command_to_lowercase(group, group_num);
}
