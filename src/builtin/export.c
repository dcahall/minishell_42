/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:47:26 by cvine             #+#    #+#             */
/*   Updated: 2022/05/07 21:24:10 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_valid_id(char *id)
{
	if (!((*id >= 'A' && *id <= 'Z') || (*id >= 'a' && *id <= 'z')
		|| *id == '_'))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(id, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
		ft_putendl_fd(ERR_UNSET, STDERR_FILENO);
		g_exit_status = 1;
	}
}


static void	print_sorted_envp(t_list **envp)
{
	int		i;
	char	**envp_copy;
	char	envp_len;

	i = 0;
	envp_copy = convert_env_lst(*envp);
	envp_len = get_2d_array_len(envp_copy);
	quicksort_2d_array(envp_copy, 0, envp_len - 1);
	while (i < envp_len)
		ft_putendl_fd(envp_copy[i++], STDOUT_FILENO);
	free_str_array(envp_copy);
}

static void	set_var(t_list **env_head, char *key, char *value)
{
	t_list	*tmp;
	t_list	*new_var;

	tmp = get_envp(*env_head, key);
	if (tmp)
	{
		free(key);
		free(tmp->content);
		tmp->content = value;
		return ;
	}
	new_var = ft_lstnew(value, key);
	ft_lstadd_back(env_head, new_var);
}

static void	export_var(char	**cmd, t_list **env_head)
{
	int		i;
	char	*key;
	char	*value;

	while (*cmd)
	{
		i = 0;
		is_valid_id(*cmd);
		value = ft_strchr_index(*cmd, '=', &i);
		if (i)
		{
			if (!value)
			{
				key = ft_strjoin(*cmd, "=");
				set_var(env_head, key, "");
			}
			else
			{
				key = ft_substr(*cmd, 0, i + 1);
				set_var(env_head, key, value + 1);
			}
		}
		cmd++;
	}
}

void	export(char	**cmd, t_list **env_head)
{
	g_exit_status = 0;
	if (!cmd[1])
		print_sorted_envp(env_head);
	else
		export_var(cmd + 1, env_head);
}
