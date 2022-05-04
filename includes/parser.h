/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:11:13 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/20 17:01:17 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdio.h>
# include <unistd.h>
# define WORD				0
# define PIPE				1
# define REDIRECT			2
# define DOUBLE_REDIRECT	3
# define SPACE				4
# define SINGLE_QUOTE		5
# define DOUBLE_QUOTE		6

int		preparser(char *cmd_line);
char	*remove_extra_spaces(char *str, int start, int end);
t_list	*parser(char *cmd_line, t_shell *shell);

/*
** Splits a string into token sheets
** Reveals what is in parentheses
*/
int	word_or_symbol(char *cmd_line, int i, t_list *token);
int	quote(char *cmd_line, int i, t_list *token);

# endif 