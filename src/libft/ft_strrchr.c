/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:06:17 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:19:17 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	n;

	n = 0;
	while (s[n] != '\0')
		n++;
	while (n != 0 && s[n] != c)
		n--;
	if (n == 0 && s[n] != c)
		return (0);
	else
		return ((char *)s + n);
}
