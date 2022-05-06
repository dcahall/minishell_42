/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:27:48 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/06 18:38:51 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(char *cmd_line, t_shell *shell)
{
	t_list	*tokens;
	
	cmd_line = remove_empty_quote(cmd_line);
	cmd_line = remove_extra_spaces(cmd_line, 0, 0);
	cmd_line = parse_dollar(cmd_line, shell);
	if (!cmd_line)
		return (EXIT_FAILURE);
	tokens = create_token_list(cmd_line);
	if (create_group(shell, tokens) == EXIT_FAILURE)
	{
		ft_lstclear(&tokens, free);
		try_free(cmd_line);
		return (EXIT_FAILURE);
	}
	ft_lstclear(&tokens, free);
	try_free(cmd_line);
	return (EXIT_SUCCESS);
}
