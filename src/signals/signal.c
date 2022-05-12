/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:15:03 by cvine             #+#    #+#             */
/*   Updated: 2022/05/12 19:15:43 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_process(int sig)
{
	(void)sig;
	g_exit_status = EXIT_FAILURE;
	write(1, "\n", 1);
}

void	ctrl_c(int sig)
{
	(void)sig;
	g_exit_status = EXIT_FAILURE;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void ft_signal(void)
{
	struct sigaction sa;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sa.sa_handler = ctrl_c;
	sigaction(SIGINT, &sa, NULL);
}