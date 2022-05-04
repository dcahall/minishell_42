/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:11:49 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/09 14:11:51 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		symbol;
	const char	*str;
	size_t		i;

	i = 0;
	symbol = c;
	while (s[i])
	{
		if (symbol == s[i])
		{
			str = &s[i];
			return ((char *) str);
		}
		i++;
	}
	if (symbol == s[i])
	{
		str = &s[i];
		return ((char *) str);
	}
	return (NULL);
}
