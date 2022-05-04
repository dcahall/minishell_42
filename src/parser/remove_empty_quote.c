/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:25:56 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/03 15:36:11 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_quote(char *str, int i)
{
	if (str[i] == '\'' || str[i] == '"')
	{
		if (str[i] == str[i + 1])
			return (1);
	}
	return (0);
}

static int	num_empty_quote(char *str)
{
	size_t	num_quote;
	int		i;

	i = 0;
	num_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (is_empty_quote(str, i))
			{
				num_quote += 2;
				i += 2;
			}
			else
				skip_quote(str, &i);
		}
		else
			i++;
	}
	return (num_quote);
}

static char	*trimm_empty_quote(char *str, char *final_str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '\'' || str[j] =='"')
			while (is_empty_quote(str, j))
				j += 2;
		final_str[i] = str[j];
		i++;
		j++;
	}
	final_str[i] = '\0';
	return (final_str);
}

char	*remove_empty_quote(char *str)
{
	size_t	empty_quote;
	char	*final_str;

	if (!str)
		return (NULL);
	empty_quote = num_empty_quote(str);
	if ((ft_strlen(str) - empty_quote) == 0)
	{
		try_free(str);
		return (NULL);
	}
	else if (empty_quote == 0)
		return (str);
	final_str = malloc(sizeof(char) * ft_strlen(str) - empty_quote);
	check_malloc_error(final_str);
	final_str = trimm_empty_quote(str, final_str);
	free(str);
	return (final_str);
}
