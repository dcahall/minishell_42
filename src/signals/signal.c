/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:15:03 by cvine             #+#    #+#             */
/*   Updated: 2022/05/16 18:31:04 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c(int sig)
{
	(void)sig;
	g_exit_status = EXIT_FAILURE;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	proc_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = EXIT_TERM_CTRL_C;
		write(1, "\n", 1);
	}
	else if (signum == SIGQUIT)
	{
		g_exit_status = EXIT_STATE_NOT_RECOV;
		write(1, "Quit: 3\n", 8);
	}
}

void	prompt_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_c;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

void	proc_signals(void)
{
	signal(SIGINT, proc_sig_handler);
	signal(SIGQUIT, proc_sig_handler);
}


void	heredoc_signals(int signum)
{
	(void)signum;
	write(1, ">   \n", 5);
	exit(EXIT_FAILURE);
}