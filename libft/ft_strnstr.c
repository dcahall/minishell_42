/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:28:13 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/09 17:28:15 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;
	size_t	h;

	n = 0;
	h = 0;
	if (!needle[n])
		return ((char *)haystack);
	while (h < len && haystack[h])
	{
		while (needle[n] == haystack[n + h] && h + n < len && haystack[h + n])
		{
			n++;
			if (!needle[n])
				return ((char *)haystack + h);
		}
		n = 0;
		h++;
	}
	return (NULL);
}
