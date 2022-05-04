/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:32:19 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/21 12:32:22 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*counter;
	int		size_list;

	size_list = 0;
	counter = lst;
	while (counter)
	{
		counter = counter -> next;
		size_list++;
	}
	return (size_list);
}
