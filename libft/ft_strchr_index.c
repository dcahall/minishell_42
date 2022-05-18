/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:37:58 by cvine             #+#    #+#             */
/*   Updated: 2022/05/18 12:19:25 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_index(const char *s, int c, int *i)
{
	while (s[*i])
	{
		if (s[*i] == (char)c)
			return ((char *)(s + *i));
		(*i)++;
	}
	if (s[*i] == c)
		return ((char *)(s + *i));
	return (NULL);
}
