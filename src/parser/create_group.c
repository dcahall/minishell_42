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

static int	num_logicagroup(t_list *tokens)
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

static void init_lgroup_shell(t_shell *shell, t_arg *group, int group_num)
{
	int	i;

	i = 0;
	shell->group_num = group_num;
	shell->group = group;
	while (i < group_num)
	{
		group[i].cmd = NULL;
		group[i].in_fd = shell->std_in;
		group[i].out_fd = shell->std_out;
		i++;
	}
}

void	create_logicagroup(t_shell *shell, t_list *tokens)
{
	t_arg	*group;
	int		group_num;

	group_num = num_logicagroup(tokens);
	group = (t_arg *)malloc(sizeof(t_arg) * group_num);
	check_malloc_error(group);
	init_lgroup_shell(shell, group, group_num);
	if (handle_all_file(shell, &tokens, group) == EXIT_FAILURE)
	{
		ft_lstclear(tokens, free);
		super_cleaner(shell);
		return (EXIT_FAILURE);
	}
	delete_used_tokens(&tokens);
	if (!tokens)
		return (EXIT_FAILURE);		
	get_command_argument(shell->group, tokens, shell->group_num);
	ft_lstclear(&tokens, free);
	return (EXIT_SUCCESS);
}
