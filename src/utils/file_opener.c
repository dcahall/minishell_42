/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:37:19 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/14 15:17:58 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file, int occasion)
{
	int	fd;

	fd = 0;
	if (occasion == REDIRECT_IN || occasion == HERE_DOC)
		fd = open(file, O_RDONLY);
	else if (occasion == REDIRECT_OUT)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (occasion == DOUBLE_REDIRECT)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		error_occured((const char *)file, NULL);
	return (fd);
}
