/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 13:17:37 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/10 13:17:39 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	long_value(unsigned long result, int negative)
{
	if (result > 2147483648 && negative == -1)
		return (0);
	else if (result > 2147483647 && negative == 1)
		return (0);
	else
		return ((int)result);
}

int	ft_atoi(const char *str)
{
	int				negative;
	unsigned long	result;

	result = 0;
	negative = 1;
	if (!str)
		return (0);
	while ((*str >= 0 && *str <= 32) || *str == 127)
	{
		if (*str == 27)
			return (0);
		str++;
	}
	if (*str == 43)
		str++;
	else if (*str == 45 && ++str)
		negative = -1;
	if (ft_strlen(str) > 10)
		return (0);
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (long_value(result, negative));
}
