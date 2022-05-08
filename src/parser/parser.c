/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:27:48 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/07 17:22:04 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (create_group(shell, &tokens) == EXIT_FAILURE)
	{
		ft_lstclear(&tokens, free);
		try_free(cmd_line);
		return (EXIT_FAILURE);
	}
	ft_lstclear(&tokens, free);
	try_free(cmd_line);
	return (EXIT_SUCCESS);
}
