/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:33:38 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:28:02 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)arr;
	while (n > 0)
	{
		if (*s == (unsigned char)c)
			return ((void *)s);
		s++;
		n--;
	}
	return (0);
}
