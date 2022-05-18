/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_occured.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:20:27 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/18 15:20:06 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_occured(const char *the_reason, char *error_message)
{
	if (error_message == NULL)
		error_message = strerror(errno);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)the_reason, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd((char *)error_message, STDERR_FILENO);
	g_exit_status = EXIT_CMD_NOT_FOUND;
}
