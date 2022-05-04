/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:34:41 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/09 14:34:42 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		symbol;
	const char	*str;
	int			i;

	i = 0;
	symbol = c;
	str = s;
	while (*str)
	{
		if (*str == symbol)
		{
			s = str;
			i++;
		}
		str++;
	}
	if (*str == symbol)
		return ((char *)str);
	else if (i != 0)
		return ((char *)s);
	return (NULL);
}
