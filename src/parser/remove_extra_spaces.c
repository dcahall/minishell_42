/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_extra_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:53:00 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/27 20:43:44 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quote(char *str, int *i)
{
	char	remember_quote;

	remember_quote = str[*i];
	*i += 1;
	while (str[*i] != remember_quote)
		*i += 1;
	*i += 1;
}

static void	skip_space(char *str, int *start, int *end)
{
	*end += 1;
	if (str[*end] == ' ' || (str[*end] >= 8 && str[*end] <= 13))
	{
		while (str[*end] == ' ' || (str[*end] >= 8 && str[*end] <= 13))
			*end += 1;
	*start = *end;
	}
}

static char	*get_str(char *str, char *final_str, int start, int end)
{
	char	*tmp;
	char	*tmp2;

	tmp = final_str;
	if (final_str)
	{
		tmp2 = ft_substr(str, start, end - start + 1);
		final_str = ft_strjoin(final_str, tmp2);
		free(tmp2);
	}
	else
		final_str = ft_substr(str, start, end - start + 1);
	check_malloc_error(final_str);
	free(tmp);
	return (final_str);
}

static char	*trimm_tip(char *str)
{
	char	*tmp;

	tmp = str;
	str = ft_strtrim(str, "\b\t\n\b\f\r ");
	check_malloc_error(str);
	free(tmp);
	return (str);
}

char	*remove_extra_spaces(char *str, int start, int end)
{
	char	*final_str;

	final_str = NULL;
	if (!str)
		return (NULL);
	while (str[end])
	{
		if (str[end] == ' ' || (str[end] >= 8 && str[end] <= 13))
		{
			if (str[end + 1] == ' ' || (str[end + 1] >= 8
					&& str[end + 1] <= 13))
			{
				final_str = get_str(str, final_str, start, end);
			}
			skip_space(str, &start, &end);
		}
		else if (str[end] == '\'' || str[end] == '"')
			skip_quote(str, &end);
		else
			end++;
	}
	final_str = get_str(str, final_str, start, end);
	final_str = trimm_tip(final_str);
	free(str);
	return (final_str);
}
