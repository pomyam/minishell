/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:29:06 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:30:31 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_itoadigit(int n)
{
	char	*str;

	if (n >= 0)
	{
		str = (char *)malloc(2);
		if (str != NULL)
		{
			str[0] = n + '0';
			str[1] = '\0';
		}
	}
	else
	{
		str = (char *)malloc(3);
		if (str != NULL)
		{
			str[0] = '-';
			n = n * -1;
			str[1] = n + '0';
			str[2] = '\0';
		}
	}
	return (str);
}

static	int	char_count(int n)
{
	long	m;
	int		i;

	i = 0;
	m = n;
	if (n < 0)
		m = m * -1;
	while (m != 0)
	{
		m = m / 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}

static void	ft_fill_str(char *str, long first, int i)
{
	while (i >= 0)
	{
		str[i] = (first % 10) + '0';
		first = first / 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	long	first;
	int		i;
	char	*str;

	i = 0;
	first = n;
	if (n > -10 && n < 10)
	{
		str = ft_itoadigit(n);
		return (str);
	}
	i = char_count(n);
	str = (char *)malloc(i + 1);
	if (str != NULL)
	{
		str[i] = '\0';
		i--;
		if (n < 0)
			first = first * -1;
		ft_fill_str(str, first, i);
		if (n < 0)
			str[0] = '-';
	}
	return (str);
}
