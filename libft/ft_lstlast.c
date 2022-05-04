/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:51:51 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/21 12:51:53 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*check;

	check = lst;
	if (!lst)
		return (NULL);
	while (check)
	{
		if (check -> next == NULL)
			return (check);
		check = check -> next;
	}
	return (NULL);
}
