/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:44:46 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:21:29 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*n1;
	char	*n2;

	n1 = (char *)s1;
	n2 = (char *)s2;
	if (n == 0)
		return (0);
	n = n - 1;
	while (*n1 == *n2 && n > 0 && *n1)
	{
		n1++;
		n2++;
		n--;
	}
	return ((unsigned char)*n1 - (unsigned char)*n2);
}
