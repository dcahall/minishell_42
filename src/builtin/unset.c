/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:52:32 by cvine             #+#    #+#             */
/*   Updated: 2022/05/07 21:25:58 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	is_valid_id(char *id)
// {
// 	int	i;

// 	i = 0;
// 	if (!((*id >= 'A' && *id <= 'Z') || (*id >= 'a' && *id <= 'z') || *id == '_'))
// 	{
// 		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
// 		ft_putstr_fd(id, STDERR_FILENO);
// 		ft_putstr_fd("': ", STDERR_FILENO);
// 		ft_putendl_fd(ERR_UNSET, STDERR_FILENO);
// 		g_exit_status = 1;
// 	}
// 	while (id[i])
// 	{
// 		if (id[i] == '=')
// 		{
// 			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
// 			ft_putstr_fd(id, STDERR_FILENO);
// 			ft_putstr_fd("': ", STDERR_FILENO);
// 			ft_putendl_fd(ERR_UNSET, STDERR_FILENO);
// 			g_exit_status = 1;
// 		}
// 		i++;
// 	}
	
// }

// static void	unset_var(char	**cmd, t_list **env_head)
// {
// 	int		i;
// 	char	**var;
// 	char	*key;
// 	t_list	*tmp;

// 	while (*cmd)
// 	{
// 		i = 0;
// 		is_valid_id(*cmd);
// 		key = ft_strjoin(*var, "=");
// 		tmp = get_envp(*env_head, key);
// 		if (tmp)
// 			del_env_param(env_head, key);
// 		cmd++;
// 	}
// }

// void	unset(char **cmd, t_list **env_head)
// {
// 	g_exit_status = 0;
// 	if (!cmd[1])
// 		return ;
// 	unset_var(cmd, env_head);
// }
