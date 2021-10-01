/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:47:02 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:28:25 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char		*ndest;
	unsigned char		*nsource;
	unsigned char		i;

	ndest = (unsigned char *)destination;
	nsource = (unsigned char *)source;
	i = (unsigned char)c;
	if (n == 0)
		return (0);
	while (n > 0 && *nsource != i)
	{
		*ndest = *nsource;
		ndest++;
		nsource++;
		n--;
	}
	if (*nsource == i)
	{
		*ndest = i;
		return (ndest + 1);
	}
	else
		return (0);
}
