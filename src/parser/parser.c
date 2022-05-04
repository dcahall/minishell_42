/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:27:48 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/04 21:14:24 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(char *cmd_line, t_shell *shell)
{
	t_list	*tokens;
	t_list	*tmp;
	int		i;
	
	i = 0;
	cmd_line = remove_empty_quote(cmd_line);
	cmd_line = remove_extra_spaces(cmd_line, 0, 0);
	cmd_line = parse_dollar(cmd_line, shell);
	if (!cmd_line)
		return (EXIT_FAILURE);
	while (cmd_line[i])
	{
		tmp = ft_lstnew(NULL, NULL);
		check_malloc_error(tmp);
		ft_lstadd_back(&tokens, tmp);
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
			i = quote(cmd_line, i, tmp);
		else
			i = word_or_symbol(cmd_line, i, tmp);
	}
	// if (create_group(shell, tokens) == EXIT_FAILURE)
	// {
	// 	try_free(cmd_line);
	// 	return (EXIT_FAILURE);
	// }
	try_free(cmd_line);
	return (EXIT_SUCCESS);
}
