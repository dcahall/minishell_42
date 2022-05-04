/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:56:24 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:12:57 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_file_fd(t_shell *shell, t_arg *group, t_list *tokens, \
						int token_type)
{
	int		fd;

	fd = open_file(tokens->content, token_type);
	if (fd == EXIT_FAILURE)
	{
		release_fd(shell);
		return (EXIT_FAILURE);
	}
	if (token_type == REDIRECT_IN)
		group->in_fd = fd;
	else if (token_type == DOUBLE_REDIRECT || token_type == REDIRECT_OUT)
		group->out_fd = fd;
	return (EXIT_SUCCESS);
}

int	handle_all_file(t_shell *shell, t_list **tokens, t_arg *group)
{
	t_list	*runner;
	int		i;

	i = 0;
	runner = *tokens;
	while (runner)
	{
		if (runner->type == PIPE)
		{
			group[i].out_fd = PIPE;
			group[i + 1].in_fd = PIPE;
			i++;
		}
		else if (runner->type == HERE_DOC)
			group[i].limiter = ft_strdup(runner->next->content);
		else if (runner->type == REDIRECT_IN || runner->type == REDIRECT_OUT
			|| runner->type == DOUBLE_REDIRECT)
		{
			if (get_file_fd(shell, group[i], runner->next, \
				runner->type) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		runner = runner->next;
	}
	return (EXIT_SUCCESS);
}