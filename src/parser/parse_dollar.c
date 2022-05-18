/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:30:27 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/18 16:17:46 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_new_start(char *add)
{
	if (!add)
		return (0);
	return (ft_strlen(add));
}

static char	*handle_dollar( char *str, char **envp, int *start)
{
	char	*add_str;
	int		len;

	len = 1;
	if (str[*start + 1] == '?')
	{
		add_str = ft_itoa(g_exit_status);
		len = ft_strlen(add_str);
		str = add_piece_to_str(add_str, str, *start, *start + 2);
	}
	else if (ft_isalnum(str[*start + 1]) || str[*start + 1] == '_')
	{
		add_str = find_env(envp, str, *start + 1);
		len = find_new_start(add_str);
		str = add_piece_to_str(add_str, str, *start, \
		end_path_name(str, *start + 1));
	}
	*start = *start + len;
	return (str);
}

char	*parse_dollar(char *cmd_line, t_shell *shell)
{
	int	i;

	i = 0;
	if (!cmd_line)
		return (NULL);
	while (cmd_line && cmd_line[i])
	{
		if (cmd_line[i] == '\'')
			skip_quote(cmd_line, &i);
		else if (cmd_line[i] == '$')
		{
			if (shell->env_str)
				free_str_array(shell->env_str);
			shell->env_str = convert_env_lst(shell->env_lst);
			cmd_line = handle_dollar(cmd_line, shell->env_str, &i);
		}
		else
			i++;
	}
	return (cmd_line);
}
