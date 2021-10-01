/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:41:05 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:15:47 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_check(char c, char const *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

static size_t	len_back(const char *s1, char const *set)
{
	size_t	len_end;

	len_end = 0;
	while (*s1 && set_check(*s1, set) == 1)
	{
		s1--;
		len_end++;
	}
	return (len_end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*old;
	size_t	len_beg;

	len_beg = 0;
	old = (char *)s1;
	if (!s1)
		return (0);
	if (!set && ft_strdup(s1) != NULL)
		return (ft_strdup(s1));
	while (*s1 && set_check(*s1, set) == 1)
	{
		s1++;
		len_beg++;
	}
	if ((*s1 == '\0') && ft_strdup(s1) != NULL)
		return (ft_strdup(s1));
	s1 = old + (ft_strlen(old) - 1);
	if (ft_substr(old, len_beg, ft_strlen(old) - (len_beg + len_back(s1, set))))
	{
		return (ft_substr(old,
				len_beg, (ft_strlen(old) - (len_beg + len_back(s1, set)))));
	}
	return (NULL);
}
