/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:50:42 by lruncorn          #+#    #+#             */
/*   Updated: 2020/11/13 18:41:03 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*result;
	unsigned int	n;

	if (!s)
		return (0);
	n = 0;
	len = ft_strlen(s);
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (0);
	while (s[n] != '\0')
	{
		result[n] = f(n, s[n]);
		n++;
	}
	result[n] = '\0';
	return (result);
}
