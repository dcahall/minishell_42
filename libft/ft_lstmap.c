/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:43:00 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/30 17:27:44 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*copy_list;
	t_list	*helper;

	helper = NULL;
	if (!lst && !f && !del)
		return (NULL);
	while (lst)
	{
		copy_list = ft_lstnew(f(lst -> content), lst->key);
		if (copy_list == NULL)
		{
			ft_lstclear(&helper, del);
			return (helper);
		}
		ft_lstadd_back(&helper, copy_list);
		lst = lst -> next;
	}
	return (helper);
}
