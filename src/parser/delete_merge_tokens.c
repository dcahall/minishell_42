/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_merge_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:03:42 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/07 14:23:17 by dcahall          ###   ########.fr       */
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
		ft_lstdelone(tmp, free);
		*tokens = runner;
		return ;
	}
	while (runner)
	{
		if (runner == delete)
		{
			tmp->next = runner->next;
			ft_lstdelone(runner, free);
			return ;
		}
		tmp = tmp->next;
		runner = runner->next;
	}
}

void	merge_tokens(t_list **tokens)
{
	t_list	*runner;
	t_list	*tmp1;
	char	*tmp2;

	if (!*tokens)
		return ;
	runner = *tokens;
	while (runner->next)
	{
		tmp1 = runner->next;
		if ((runner->type == WORD || runner->type == SINGLE_QUOTE
				|| runner->type == DOUBLE_QUOTE) && (tmp1->type == WORD
				|| tmp1->type == SINGLE_QUOTE || tmp1->type == DOUBLE_QUOTE))
		{
			tmp2 = runner->content;
			runner->content = ft_strjoin(runner->content, tmp1->content);
			check_malloc_error(runner->content);
			try_free(tmp2);
			del_elem(tokens, tmp1);
		}
		else
			runner = runner->next;
	}
}

void	delete_empty_tokens(t_list **tokens)
{
	t_list	*runner;

	if (!*tokens)
		return ;
	runner = *tokens;
	while (runner && runner->type == EMPTY)
	{
		*tokens = runner->next;
		ft_lstdelone(runner, free);
		runner = *tokens;
	}
	while (runner && runner->next)
	{
		while (runner->next && runner->next->type == EMPTY)
			del_elem(tokens, runner->next);
		runner = runner->next;
	}
}	

void	delete_file_tokens(t_list **tokens)
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
			del_elem(tokens, delete2);
			del_elem(tokens, delete1);
		}
		else
			runner = runner->next;
	}
}
