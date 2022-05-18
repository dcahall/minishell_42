/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:47:26 by cvine             #+#    #+#             */
/*   Updated: 2022/05/18 14:47:32 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		tmp->content = value;
		return ;
	}
	new_var = ft_lstnew(value, key);
	ft_lstadd_back(env_head, new_var);
}

static void	set_new_var(char **arg, t_list **env_head)
{
	int		equal_index;
	char	*key;
	char	*value;
	char	*equal_location;

	while (*arg)
	{
		equal_index = 0;
		if (!is_valid_id(*arg, "export `", EXPORT))
		{
			equal_location = ft_strchr_index(*arg, '=', &equal_index);
			if (!equal_location)
			{
				key = ft_strjoin(*arg, "=");
				set_var(env_head, key, "");
			}
			else
			{
				key = ft_substr(*arg, 0, equal_index + 1);
				value = ft_strdup(equal_location + 1);
				set_var(env_head, key, value);
			}
		}
		arg++;
	}
}

void	export(char	**cmd, t_list **env_head)
{
	g_exit_status = EXIT_SUCCESS;
	if (!cmd[1])
		print_sorted_envp(env_head);
	else
		set_new_var(cmd + 1, env_head);
}
