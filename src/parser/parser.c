/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:27:48 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/16 16:08:56 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_string(const char *cmd_line, int *i)
{
	while (cmd_line[*i] && ft_isspace(cmd_line[*i]))
		*i += 1;
	if (cmd_line[*i] == '\0')
		return (1);
	return (0);
}

int	parser(char *cmd_line, t_shell *shell)
{
	t_list	*tokens;
	int		tmp;

	tmp = 0;
	cmd_line = remove_empty_quote(cmd_line);
	if (check_empty_string(cmd_line, &tmp))
	{
		free(cmd_line);
		return (EXIT_FAILURE);
	}
	cmd_line = remove_extra_spaces(cmd_line, 0, 0);
	cmd_line = parse_dollar(cmd_line, shell);
	if (!cmd_line)
		return (EXIT_FAILURE);
	tokens = create_token_list(cmd_line);
	create_group(shell, &tokens);
	ft_lstclear(&tokens, free);
	try_free(cmd_line);
	return (EXIT_SUCCESS);
}
