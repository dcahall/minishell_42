/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:17:23 by cvine             #+#    #+#             */
/*   Updated: 2022/05/11 19:22:59 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_f	get_builtin(char **cmd, t_builtin *builtin)
{
	int	i;

	i = 0;
	while (i < NUM_OF_BUILTIN)
	{
		if (!ft_strcmp(*cmd, builtin[i].name))
			return (builtin[i].func);
		i++;
	}
	return (NULL);
}