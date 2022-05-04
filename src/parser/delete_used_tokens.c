/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_used_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:03:42 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/03 19:24:10 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_elem(t_list **tokens, t_list *delete)
{
	t_list	*tmp;
	t_list	*runner;

	if (!tokens || !delete)
		return ;
	tmp = *tokens;
	runner = tmp->next;
	if (tmp == delete)
	{
		ft_lstdelone(tmp);
		*tokens = runner;
		return ;
	}
	while (runner)
	{
		if (runner == delete)
		{
			tmp->next = runner->next;
			ft_lstdelone(runner, free);
		}
		tmp = tmp->next;
		runner = runner->next;
	}
}

static void	unit_quote_tokens(t_list **tokens)
{
	t_list	*runner;
	char	*tmp;

	if (!*tokens)
		return ;
	runner = *tokens;
	while (runner)
	{
		while (runner->type != PIPE && runner->type != SPACE && runner->next
			&& runner->next->type != PIPE && runner->next->type != SPACE)
		{
			tmp = runner->content;
			runner->content = ft_strjoin(runner->content, runner->next->content);
			check_malloc_error(runner->content);
			try_free(tmp);
			del_elem(tokens, runner->next);
		}
		runner = runner->next;
	}
}

static void	delete_space_tokens(t_list **tokens)
{
	t_list	*runner;

	if (!*tokens)
		return ;
	runner = *tokens;
	while (runner && runner->type == SPACE)
	{get_command_to_execve.c
		*tokens = runner->next;
		ft_lstdelone(runner, free);
		runner = *tokens;
	}
	while (runner->next)
	{
		while (runner->next && runner->next->type == SPACE)
			del_elem(tokens, runner->next);
		runner = runner->next;
	}
}	

void	delete_used_tokens(t_list **tokens)
{
	t_list	*delete1;
	t_list	*delete2;
	t_list	*runner;

	runner = *tokens;
	delete1 = NULL;
	delete2 = NULL;
	while (runner)
	{
		if (runner->type == REDIRECT_IN || runner->type == REDIRECT_OUT
			|| runner->type == DOUBLE_REDIRECT || runner->type == HERE_DOC)
		{
			delete1 = runner;
			delete2 = runner->next;
			runner = runner->next->next;
			del_elem(tokens, delete1);
			del_elem(tokens, delete2);
		}
		else
			runner = runner->next;
	}
	unit_quote_tokens(tokens);
	delete_space_tokens(tokens);
}
