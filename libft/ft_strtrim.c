/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:10:25 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/15 18:10:26 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_proverka1(char const s1, char const *set)
{
	while (*set)
	{
		if (*set == s1)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimm;

	start = 0;
	if (!set || !s1)
		return (NULL);
	end = ft_strlen(s1) - 1;
	trimm = NULL;
	while (ft_proverka1(s1[start], set) == 1 && s1[start]
		&& start < ft_strlen(s1))
		start++;
	while (ft_proverka1(s1[end], set) == 1 && start < ft_strlen(s1))
		end--;
	trimm = ft_substr(s1, start, (end - start + 1));
	return (trimm);
}
