/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:43:07 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/03 16:31:51 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_symbol(char *cmd_line, int i, t_list *token)
{
	if ((cmd_line[i] == '>' || cmd_line[i] == '<')
		&& cmd_line[i] == cmd_line[i + 1])
	{
		token->content = ft_substr(cmd_line, i, 2);
		token->type = DOUBLE_REDIRECT;
		if (cmd_line[i] == '<')
			token->type = HERE_DOC;
		return (i + 2);
	}

	if (ft_isspace(cmd_line[i]) == 0)
	{
		if (cmd_line[i] == '|')
			token->type = PIPE;
		else if (cmd_line[i] == '>')
			token->type = REDIRECT_OUT;
		else if (cmd_line[i] == '<')
			token->type = REDIRECT_IN;
		token->content = ft_substr(cmd_line, i, 1);
	}
	else
	{
		token->type = SPACE;
		token->content = ft_substr(" ", 0, 1);
	}
	return (i + 1);
}

int	word_or_symbol(char *cmd_line, int i, t_list *token)
{
	int	start;

	start = i;
	if (cmd_line[i] == '>' || cmd_line[i] == '<' || cmd_line[i] == '|'
		|| cmd_line[i] == ' ')
		return (single_symbol(cmd_line, i, token));
	while (cmd_line[i] && cmd_line[i] != '>' && cmd_line[i] != '<'
		&& cmd_line[i] != '"' && cmd_line[i] != '\'' && cmd_line[i] != '|'
		&& !ft_isspace(cmd_line[i]))
		i++;
	token->content = ft_substr(cmd_line, start, i - start);
	token->type = WORD;
	return (i);
}

int	quote(char *cmd_line, int i, t_list *token)
{
	char	remember_quote;
	char	start;

	remember_quote = cmd_line[i];
	i++;
	start = i;
	while (cmd_line[i] != remember_quote)
		i++;
	if (token->content == NULL)
		token->content = ft_substr(cmd_line, start, i - start);
	if (remember_quote == '\'')
		token->type = SINGLE_QUOTE;
	else
		token->type = DOUBLE_QUOTE;
	return (i + 1);
}
