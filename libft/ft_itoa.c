/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:47:58 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/16 18:48:02 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenght(int len)
{
	int	i;

	i = 0;
	if (len < 0)
	{
		len = -len;
		i++;
	}
	while (len > 9)
	{
		len = len / 10;
		i++;
	}
	return (i);
}

static char	*ft_putnbr_exp(int number, char *str, int i)
{
	str[i - 1] = '\0';
	i -= 2;
	if (number < 0)
	{
		number = -number;
		str[0] = 45;
	}
	if (number == 0)
	{
		str[0] = 48;
		return (str);
	}
	while (number > 0)
	{
		str[i] = number % 10 + '0';
		number = number / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	j;
	char			*str;

	j = n;
	i = lenght(j) + 2;
	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	str = (char *) malloc(i);
	if (!str)
		return (NULL);
	return (ft_putnbr_exp(n, str, i));
}
