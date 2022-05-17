/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:15:41 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/16 16:15:54 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtin(t_shell *shell)
{
	shell->builtin[0].name = "cd";
	shell->builtin[0].func = cd;
	shell->builtin[1].name = "pwd";
	shell->builtin[1].func = pwd;
	shell->builtin[2].name = "env";
	shell->builtin[2].func = env;
	shell->builtin[3].name = "echo";
	shell->builtin[3].func = echo;
	shell->builtin[4].name = "export";
	shell->builtin[4].func = export;
	shell->builtin[5].name = "exit";
	shell->builtin[5].func = ft_exit;
	shell->builtin[6].name = "unset";
	shell->builtin[6].func = unset;
}
