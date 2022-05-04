/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:32:59 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/10 17:33:01 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	s;
	size_t	d;
	size_t	result;

	s = 0;
	d = ft_strlen(dst);
	if (ft_strlen(dst) > dstsize)
	{
		result = ft_strlen(src) + dstsize;
		return (result);
	}
	else
		result = ft_strlen(dst) + ft_strlen(src);
	if (dstsize == 0)
		return (result);
	while (d < dstsize - 1 && src[s])
	{
		dst[d] = src[s];
		d++;
		s++;
	}
	dst[d] = '\0';
	return (result);
}
