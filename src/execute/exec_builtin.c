/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:44:59 by cvine             #+#    #+#             */
/*   Updated: 2022/05/09 11:45:23 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_func	get_builtin(char **cmd, t_builtin *builtin)
{
	int	i;

	i = 0;
	while (i < NUM_OF_BUILTIN)
	{
		if (!ft_strcmp(*cmd, builtin[i].name))
			return (builtin[i].func_ptr);
		i++;
	}
	return (NULL);
}

void	exec_builtin(t_shell *shell, char **cmd)
{
	t_builtin_func	builtin;

	builtin = get_builtin(cmd, shell->builtin);
	builtin(cmd, &shell->env_lst);
}
