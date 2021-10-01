/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:55:39 by lruncorn          #+#    #+#             */
/*   Updated: 2020/11/10 17:06:16 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	sub = NULL;
	if (!s)
		return (0);
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (0);
	if (start < ft_strlen(s))
	{
		s = s + start;
		while (*s && i < len)
		{
			sub[i] = *s;
			s++;
			i++;
		}
		sub[i] = '\0';
	}
	return (sub);
}
