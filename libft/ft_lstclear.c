/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:56:26 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/30 20:29:59 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*delete;

	delete = *lst;
	if (!lst || !del)
		return ;
	while (delete != NULL)
	{
		delete = delete -> next;
		if ((*lst)->content)
			(*del)((*lst)-> content);
		if ((*lst)->key)
			(*del)((*lst)-> key);
		free ((*lst));
		*lst = delete;
	}
	*lst = NULL;
}
