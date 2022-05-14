/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:56:24 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/12 16:53:22 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_file_fd(t_shell *shell, t_arg *group, t_list *tokens, \
						int token_type)
{
	int		fd;

	fd = open_file(tokens->content, token_type);
	if (token_type == REDIRECT_IN)
	{
		if (group->in_fd != shell->std_in)
			close(group->in_fd);
		group->in_fd = fd;
	}
	else if ((token_type == DOUBLE_REDIRECT || token_type == REDIRECT_OUT))
	{
		if (group->out_fd != PIPE && group->out_fd != shell->std_out)
			close(group->out_fd);
		group->out_fd = fd;
	}
	else if (token_type == HERE_DOC)
		group->heredoc_fd[group->heredoc_fd_num] = fd;
}

void	handle_all_file(t_shell *shell, t_list **tokens, t_arg *group)
{
	t_list	*runner;
	int		i;

	i = 0;
	runner = *tokens;
	while (runner)
	{
		if (runner->type == PIPE && group[i + 1].in_fd == shell->std_in)
		{
			group[i + 1].in_fd = PIPE;
			i++;
		}
		else if (runner->type == REDIRECT_IN || runner->type == REDIRECT_OUT
			|| runner->type == DOUBLE_REDIRECT)
			get_file_fd(shell, &group[i], runner->next, runner->type);
		runner = runner->next;
	}
	shell->out_fd = group[i].out_fd;
}

static void	malloc_array_fd(t_arg *group, t_list *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		i++;
		tokens = tokens->next;
	}
	group->heredoc_fd = malloc(sizeof(int) * i);
	check_malloc_error(group->heredoc_fd);
}

t_list	*handle_heredoc_files(t_shell *shell, t_arg *group, t_list *tokens)
{
	int		heredoc_fd_num;

	heredoc_fd_num = 0;
	close(group->in_fd);
	malloc_array_fd(group, tokens);
	while (tokens && tokens->type != PIPE)
	{
		group->heredoc_fd_num = heredoc_fd_num;
		get_file_fd(shell, group, tokens, REDIRECT_IN);
		heredoc_fd_num++;
		tokens = tokens->next;
	}
	group->heredoc_fd_num = heredoc_fd_num;
	return (tokens);
}
