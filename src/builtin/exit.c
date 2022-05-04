/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:52:13 by cvine             #+#    #+#             */
/*   Updated: 2022/05/04 20:33:43 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_with_error(const char *arg)
{
	ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(OUT_OF_RANGE);
}

static void	exit_with_status(unsigned long long status)
{
	u_int8_t	exit_status;

	exit_status = status;
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_status);
}

static unsigned long long	atoi_llu(const char *str)
{
	int					i;
	unsigned long long	rep;
	int					minus;

	i = 0;
	rep = 0;
	minus = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		rep = rep * 10 + (str[i] - 48);
		i++;
	}
	if ((rep > INT64_MAX && minus == 1) || (rep - 1 > INT64_MAX && minus == -1))
		exit_with_error(str);
	return (rep * minus);
}

void	ft_exit(char **cmd, t_list **env_head)
{
	int	argc;

	(void)env_head;
	argc = arg_count(cmd);
	if (argc > 2)
	{
		atoi_llu(cmd[1]);
		if (!ft_isnumber(cmd[1]))
			exit_with_error(cmd[1]);
		else
			ft_putendl_fd("exit\nminishell: exit: too many arguments",
				STDERR_FILENO);
		g_exit_status = EXIT_FAILURE;
		return ;
	}
	if (cmd[1])
	{
		if (!ft_isnumber(cmd[1]))
			exit_with_error(cmd[1]);
		exit_with_status(atoi_llu(cmd[1]));
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(g_exit_status);
}
