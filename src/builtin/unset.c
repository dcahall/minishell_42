/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:52:32 by cvine             #+#    #+#             */
/*   Updated: 2022/05/08 18:12:57 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_var(const char *name, t_list **envp)
{
	t_list	*current;
	t_list	*prev;

	current = *envp;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(name, current->key))
		{
			if (!prev)
				(*envp)->next = current->next;
			else
				prev->next = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static void	unset_var(char	**cmd, t_list **env_head)
{
	char	*key;

	while (*cmd)
	{
		is_valid_id(*cmd, "unset: `", UNSET);
		key = ft_strjoin(*cmd, "=");
		if (get_envp(*env_head, key))
			delete_var(key, env_head);
		cmd++;
	}
}

void	unset(char **cmd, t_list **env_head)
{
	g_exit_status = 0;
	if (!cmd[1])
		return ;
	unset_var(cmd + 1, env_head);
}
