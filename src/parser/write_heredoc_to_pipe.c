/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heredoc_to_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:25:48 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/16 15:55:29 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*update_heredoc_str(char *str, char *add)
{
	char	*tmp;

	if (!str)
	{
		str = ft_strdup(add);
		free(add);
		return (str);
	}
	tmp = str;
	str = ft_strjoin(str, "\n");
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, add);
	check_malloc_error(str);
	free(add);
	free(tmp);
	return (str);
}

static void	child(char *limiter, int *pipe_fd)
{
	char	*tmp;
	char	*res_str;

	res_str = NULL;
	while (1)
	{
		tmp = readline("> ");
		if (!tmp && !*tmp)
			exit(EXIT_SUCCESS);
		else if (!*tmp)
			free(tmp);
		else if (ft_strncmp(limiter, tmp, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == ft_strlen(tmp))
			break ;
		else
			res_str = update_heredoc_str(res_str, tmp);
	}
	try_free(tmp);
	write(pipe_fd[1], res_str, ft_strlen(res_str));
	write(pipe_fd[1], "\n", 1);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	try_free(res_str);
}

void	write_heredoc_to_pipe(t_arg *group, char *limiter)
{
	int		id;
	int		pipe_fd[2];
	int		exit_status;

	signal(SIGINT, SIG_IGN);
	if (pipe(pipe_fd))
		exit(EXIT_FAILURE);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, heredoc_signals);
		child(limiter, pipe_fd);
	}
	close(pipe_fd[1]);
	waitpid(id, &exit_status, 0);
	if (WIFEXITED(exit_status))
		g_exit_status = WEXITSTATUS(exit_status);
	group->in_fd = pipe_fd[0];
}
