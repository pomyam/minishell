/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:38:03 by lruncorn          #+#    #+#             */
/*   Updated: 2020/11/04 16:01:46 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	m;
	char	*copy;

	copy = destination;
	m = 0;
	while (m < n)
	{
		copy[m] = (unsigned char)c;
		m++;
	}
	return (copy);
}
