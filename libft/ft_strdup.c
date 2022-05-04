/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:09:09 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/12 15:28:46 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*copy;
	size_t		i;

	copy = NULL;
	i = ft_strlen(s1);
	copy = (char *) malloc(sizeof(char) * (i + 1));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s1, i + 1);
	return (copy);
}
