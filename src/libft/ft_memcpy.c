/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:52:38 by lruncorn          #+#    #+#             */
/*   Updated: 2020/11/04 17:45:03 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	char		*ndest;
	const char	*nsource;
	size_t		m;

	ndest = destination;
	nsource = source;
	if (ndest == 0 && nsource == 0)
		return (0);
	else
	{
		m = 0;
		while (m != n)
		{
			ndest[m] = nsource[m];
			m++;
		}
	}
	return (ndest);
}
