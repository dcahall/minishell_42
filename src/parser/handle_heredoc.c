/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:41:50 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/16 12:30:00 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*delete_heredoc_tokens(t_list **tokens)
{
	t_list	*delete1;
	t_list	*delete2;
	t_list	*cmd_token;
	t_list	*runner;

	cmd_token = *tokens;
	runner = cmd_token;
	if (cmd_token->type == HERE_DOC)
		cmd_token = cmd_token->next->next;
	else
	{
		runner = cmd_token->next;
		while (runner->type != HERE_DOC)
		{
			runner = runner->next;
			cmd_token = cmd_token->next;	
		}
	}
	if (cmd_token && cmd_token->type == PIPE)
		cmd_token = cmd_token->next->next->next;
	delete1 = runner;
	delete2 = runner->next;
	del_elem(tokens, delete2);
	del_elem(tokens, delete1);
	return (cmd_token);
}

static t_list	*processing_heredoc(t_shell *shell, t_arg *group, \
									t_list **token_group, t_list **all_tokens)
{
	t_list	*runner;

	runner = *token_group;
	write_heredoc_to_pipe(group, group->limiter);
	if (group->in_fd == shell->std_in)
	{
		while (runner && runner->type != PIPE)
			runner = runner->next;
		return (runner);
	}
	runner = delete_heredoc_tokens(all_tokens);
	if (!runner || runner->type == PIPE)
		return (runner);
	group->cmd = (char **)malloc(sizeof(char *) * 2);
	check_malloc_error(group->cmd);
	group->cmd[1] = NULL;
	group->cmd[0] = ft_strdup(runner->content);
	check_malloc_error(group->cmd[0]);
	str_tolower(&group->cmd[0]);
	runner = runner->next;
	if (!runner || runner->type == PIPE)
		return (runner);
	else
		runner = handle_heredoc_files(shell, group, runner);
	return (runner);
}

void	handle_heredoc(t_shell *shell, t_list **tokens)
{
	t_list	*runner;
	t_list	*tmp;
	t_list	*group_start;
	int		i;

	i = 0;
	runner = *tokens;
	group_start = *tokens;
	tmp = NULL;
	while (runner)
	{
		if (runner->type == PIPE)
		{
			tmp = runner;
			runner = runner->next;
			group_start = runner;
			i++;
		}
		else if (runner->type == HERE_DOC)
		{
			shell->group[i].limiter = runner->next->content;
			runner = processing_heredoc(shell, &shell->group[i], &group_start, \
										tokens);
			delete_heredoc_group(tokens, i);
		}
		else if (runner)
			runner = runner->next;
	}
}
