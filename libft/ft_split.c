/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:10:35 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/17 16:10:36 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_error(char **pointer)
{
	size_t	i;

	i = 0;
	while (pointer[i])
	{
		free (pointer[i]);
		i++;
	}
	free (pointer);
	return (NULL);
}

static size_t	amount_str(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static size_t	word(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

static char	**splitted(char **pointer, const char *s, char c, size_t num_str)
{
	size_t	i;
	size_t	num_word;

	i = 0;
	while (num_str--)
	{
		while (*s == c)
			s++;
		num_word = word(s, c) + 1;
		pointer[i] = (char *) malloc(num_word);
		if (pointer[i] == NULL)
			return (ft_error(pointer));
		ft_strlcpy(pointer[i], s, num_word);
		i++;
		while (*s && *s != c)
			s++;
	}
	pointer[i] = NULL;
	return (pointer);
}

char	**ft_split(char const *s, char c)
{
	char	**pointer;
	size_t	num_str;

	if (!s)
		return (NULL);
	num_str = amount_str(s, c);
	pointer = (char **) malloc(sizeof(char *) * (num_str + 1));
	if (pointer == NULL)
		return (NULL);
	pointer = splitted(pointer, s, c, num_str);
	return (pointer);
}
