/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:18:10 by lruncorn          #+#    #+#             */
/*   Updated: 2020/11/09 19:33:05 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	n;
	char	*src1;
	char	*copy;

	src1 = (char *)src;
	n = ft_strlen(src);
	copy = (char *)malloc(n + 1);
	if (copy == NULL)
		return (0);
	ft_strlcpy(copy, src1, n + 1);
	return (copy);
}
