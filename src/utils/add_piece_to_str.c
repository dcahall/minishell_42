/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_piece_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:40:01 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/27 15:40:12 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_three_parts(char *add, char *str, int start, int end)
{
	char	*tmp1;
	char	*tmp2;
	char	*res_str;


	tmp1 = ft_substr(str, 0, start);
	res_str = ft_strjoin(tmp1, add);
	try_free(tmp1);
	tmp1 = res_str;
	tmp2 = ft_substr(str, end, ft_strlen(str) - end);
	res_str = ft_strjoin(res_str, tmp2);
	try_free(tmp1);
	try_free(tmp2);
	return (res_str);
}

static char	*get_one_part(char *add, char *str, int start, int end)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (start == 0 && len_str == end)
		return (add);
	else if (len_str == end && add == NULL)
		return (ft_substr(str, 0, start));
	else if (add == NULL && start == 0)
		return (ft_substr(str, end, len_str - end));
	return (NULL);
}

static char	*fuck_norminette(char *str, int start, int end, int len_str)
{
	char	*tmp1;
	char	*tmp2;
	char	*res_str;

	tmp1 = ft_substr(str, 0, start);
	tmp2 = ft_substr(str, end, len_str - end);
	res_str = ft_strjoin(tmp1, tmp2);
	try_free(tmp2);
	try_free(tmp1);
	return (res_str);
}

static char *join_two_parts(char *add, char *str, int start, int end)
{
	int		len_str;
	char 	*tmp1;
	char	*res_str;

	res_str = NULL;
	tmp1 = NULL;
	len_str = ft_strlen(str);
	if (end == len_str)
	{
		tmp1 = ft_substr(str, 0, start);
		res_str = ft_strjoin(tmp1, add);
	}
	else if (start == 0)
	{
		tmp1 = ft_substr(str, end, len_str - end);
		res_str = ft_strjoin(add, tmp1);
	}
	else if (!add)
		res_str = fuck_norminette(str, start, end, len_str);
	try_free(tmp1);
	return (res_str);
}

char	*add_piece_to_str(char *add, char *str, int start, int end)
{
	char	*res_str;
	int		len_str;

	len_str = (int)ft_strlen(str);
	if (!add && len_str == end && start == 0)
	{
		free(str);
		return (NULL);
	}
	if ((start == 0 && len_str == end) || (len_str == end && add == NULL)
		|| (add == NULL && start == 0))
		res_str = get_one_part(add, str, start, end);
	else if (start == 0 || len_str == end || add == NULL)
		res_str = join_two_parts(add, str, start, end);
	else
		res_str = join_three_parts(add, str, start, end);
	check_malloc_error(res_str);
	try_free(str);
	try_free(add);
	return (res_str);
}
