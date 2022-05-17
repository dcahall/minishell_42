/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:19:32 by dcahall           #+#    #+#             */
/*   Updated: 2022/05/16 16:46:11 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The function takes a structure where we need to write our 
** environment variable, the environment variable is divided 
** into 2 substrings: the key (up to the equal sign) and the value
*/

static void	copy_env(t_list *node, char *str)
{
	int	len_key;
	int	len_str;

	len_str = ft_strlen(str);
	len_key = len_env_key(str) + 1;
	if (len_str)
	{
		node->key = ft_substr(str, 0, len_key);
		check_malloc_error(node->key);
		if (len_key != len_str && is_empty_quote(str, len_key) == 0)
		{
			node->content = ft_substr(str, len_key, len_str - len_key);
			check_malloc_error(node->content);
		}
	}
}

/*
** The function takes a two-dimensional array of 
** environment variables and converts them into sheets
**
*/

t_list	*convert_list_char(char **envp)
{
	t_list	*env_lst;
	int		i;

	i = 0;
	env_lst = NULL;
	while (envp[i])
	{
		add_new_env(&env_lst, envp[i]);
		i++;
	}
	return (env_lst);
}

/*
** Accepts the address of the structure with environment 
** variables and the environment variable to be added, 
** allocates memory for the new element, binds it to the 
** end, and adds the variable.
*/

void	add_new_env(t_list **envp, char *new_env)
{
	t_list	*tmp;

	if (ft_strchr(new_env, '=') == NULL)
		return ;
	tmp = ft_lstnew(NULL, NULL);
	check_malloc_error(tmp);
	ft_lstadd_back(envp, tmp);
	copy_env(tmp, new_env);
}

/*
** Accepts the address of a structure with environment 
** variables  and the key of the element to be deleted. 
** If you need to delete the first element of the 
** structure, then the pointer to the head of the structure is 
** moved and the element is deleted. Otherwise, the 
** element is simply deleted
*/

void	del_env_param(t_list **envp, char *key)
{
	int		ln;
	t_list	*tmp;
	t_list	*iter;

	if (!key || !envp)
		return ;
	tmp = *envp;
	iter = tmp->next;
	ln = ft_strlen(key);
	if (len_env_key(tmp->key) == ln && ft_strncmp(tmp->key, key, ln) == 0)
	{
		ft_lstdelone(tmp, free);
		*envp = iter;
		return ;
	}
	while (iter)
	{
		if (len_env_key(iter->key) == ln && ft_strncmp(iter->key, key, ln) == 0)
		{
			tmp->next = iter->next;
			ft_lstdelone(iter, free);
		}
		tmp = tmp->next;
		iter = iter->next;
	}
}
