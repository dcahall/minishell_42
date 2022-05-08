/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_2d_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:17:38 by cvine             #+#    #+#             */
/*   Updated: 2022/05/07 18:48:32 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_2d_array(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	quicksort_2d_array(char **array, int left, int right)
{
	int	pivot;
	int	lower;
	int	greater;

	if (left < right)
	{
		lower = left;
		greater = right;
		pivot = left;
		while (lower < greater)
		{
			while (array[lower][0] <= array[pivot][0] && lower < right)
				lower++;
			while (array[greater][0] > array[pivot][0])
				greater--;
			if (lower < greater)
				swap_2d_array(&array[lower], &array[greater]);
		}
		swap_2d_array(&array[pivot], &array[greater]);
		quicksort_2d_array(array, left, greater - 1);
		quicksort_2d_array(array, greater + 1, right);
	}
}
