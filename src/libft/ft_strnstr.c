/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:54:50 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:20:22 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	if (ft_strlen(big) == 0 || ft_strlen(little) > ft_strlen(big))
		return (0);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			while (big[i + n] == little[n]
				 && little[n] != '\0' && (i + n) < len)
				n++;
			if (little[n] == '\0')
				return ((char *)&big[i]);
			else if (i + n == len)
				return (0);
		}
		i++;
		n = 0;
	}
	return (0);
}
