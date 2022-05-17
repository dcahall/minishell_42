/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 21:37:17 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/16 16:08:19 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quote(char *cmd_line, int *i)
{
	char	remember_quote;

	remember_quote = cmd_line[*i];
	*i += 1;
	while (cmd_line[*i] && cmd_line[*i] != remember_quote)
		*i += 1;
	if (cmd_line[*i] == '\0')
		return (1);
	*i += 1;
	return (0);
}

static int	check_backlash_pipe(const char *cmd_line, int *i)
{
	if (cmd_line[*i] == '|')
	{
		*i += 1;
		if (cmd_line[*i] == '|')
			return (1);
		if (check_empty_string(cmd_line, i))
			return (1);
	}
	else
	{
		*i += 1;
		if (cmd_line[*i] == '\\')
		{
			*i += 1;
			return (0);
		}
		if (check_empty_string(cmd_line, i))
			return (1);
	}
	return (0);
}

static int	check_redirect(char *cmd_line, int *i)
{
	int		runner;

	runner = 0;
	if (cmd_line[*i] == '>' && cmd_line[*i + 1] == '<')
		return (1);
	else if (cmd_line[*i] == '<' && cmd_line[*i + 1] == '>')
	{
		cmd_line[*i + 1] = ' ';
		*i += 1;
		if (check_empty_string(cmd_line, i))
			return (1);
	}
	else
	{
		while (cmd_line[*i + runner] && cmd_line[*i + runner] == cmd_line[*i])
			runner++;
		if (runner > 2)
			return (1);
		*i += runner;
		if (check_empty_string(cmd_line, i))
			return (1);
		if (cmd_line[*i] == '<' || cmd_line[*i] == '>' || cmd_line[*i] == '|')
			return (1);
	}
	return (0);
}

static int	check_extreme_cases(char *cmd_line, int *i)
{
	if (cmd_line[*i] == '\'' || cmd_line[*i] == '"')
	{
		if (check_quote(cmd_line, i))
			return (2);
	}
	else if (cmd_line[*i] == '\\' || cmd_line[*i] == '|')
	{
		if (check_backlash_pipe(cmd_line, i))
			return (2);
	}
	else if (cmd_line[*i] == '>' || cmd_line[*i] == '<')
	{
		if (check_redirect(cmd_line, i))
			return (2);
	}
	else if (cmd_line[*i] == ';')
		return (2);
	else
		*i += 1;
	return (EXIT_SUCCESS);
}

int	preparser(char *cmd_line)
{
	int	i;

	i = 0;
	if (check_empty_string(cmd_line, &i))
		return (1);
	if (cmd_line[i] == '|')
		return (2);
	while (cmd_line[i])
		if (check_extreme_cases(cmd_line, &i) == 2)
			return (2);
	return (EXIT_SUCCESS);
}
