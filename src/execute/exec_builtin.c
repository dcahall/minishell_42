/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:44:59 by cvine             #+#    #+#             */
/*   Updated: 2022/05/11 19:22:50 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_shell *shell, char **cmd)
{
	t_builtin_f	builtin;

	builtin = get_builtin(cmd, shell->builtin);
	builtin(cmd, &shell->env_lst);
}
