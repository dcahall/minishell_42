/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:41:50 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/14 14:28:39 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*delete_heredoc_tokens(t_list **tokens)
{
	t_list	*runner;
	t_list	*delete1;
	t_list	*delete2;

	runner = *tokens;
	while (runner->type != HERE_DOC)
		runner = runner->next;
	delete1 = runner;
	delete2 = runner->next;
	del_elem(tokens, delete2);
	del_elem(tokens, delete1);
	return (*tokens);
}

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

static void	write_heredoc_to_pipe(t_arg *group, char *limiter)
{
	char	*tmp;
	char	*res_str;
	int		pipe_fd[2];

	res_str = NULL;
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			return (try_free(res_str));
		else if (!*tmp)
			free(tmp);
		else if (ft_strncmp(limiter, tmp, ft_strlen(limiter)) == 0)
			break ;
		else
			res_str = update_heredoc_str(res_str, tmp);
	}
	try_free(tmp);
	if (pipe(pipe_fd))
		exit(EXIT_FAILURE);
	write(pipe_fd[1], res_str, ft_strlen(res_str));
	close(pipe_fd[1]);
	try_free(res_str);
	group->in_fd = pipe_fd[0];
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
			if (i == 0)
				*tokens = tmp;
			delete_heredoc_group(tokens, i);
		}
		else if (runner)
			runner = runner->next;
	}
}
