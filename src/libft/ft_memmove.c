/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:21:07 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:27:21 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	char	*d;
	char	*s;

	d = destination;
	s = (char *)source;
	if ((!d && !s) || n == 0)
		return (d);
	if (d < s)
		return (ft_memcpy(destination, source, n));
	else
	{
		d = d + n - 1;
		s = s + n - 1;
		while (n > 0)
		{
			*(d--) = *(s--);
			n--;
		}
	}
	return (destination);
}
