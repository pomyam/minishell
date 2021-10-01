/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:41:48 by lruncorn          #+#    #+#             */
/*   Updated: 2020/11/04 16:03:34 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	res;
	size_t	size;
	char	*ndst;
	char	*nsrc;

	res = ft_strlen(src) + ft_strlen(dst);
	ndst = dst;
	nsrc = (char *)src;
	if (ft_strlen(dst) >= dstsize)
		return (ft_strlen(src) + dstsize);
	else
	{
		size = dstsize - ft_strlen(dst);
		while (*ndst != '\0')
			ndst++;
		ft_strlcpy(ndst, nsrc, size);
	}
	return (res);
}
