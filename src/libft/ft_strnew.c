/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:10:48 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:21:02 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t len)
{
	size_t	n;
	char	*newstr;

	n = 0;
	newstr = malloc(len + 1);
	if (!(newstr))
		return (NULL);
	while (n <= len)
	{
		newstr[n] = '\0';
		n++;
	}
	return (newstr);
}
