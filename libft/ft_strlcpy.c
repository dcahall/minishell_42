/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:43:02 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/11 17:43:03 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	char	*d;
	char	*s;

	d = dst;
	s = (char *)src;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dstsize-- > 1 && *s)
	{
		*d = *s;
		d++;
		s++;
	}
	*d = '\0';
	return (ft_strlen(src));
}
