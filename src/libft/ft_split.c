/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:49:58 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:26:35 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	size_t	n;

	n = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
			n++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (n);
}

static int	ft_letter_count(char const *s, char c)
{
	size_t	n;

	n = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		n++;
	}
	return (n);
}

static void	ft_mem_free(char **s, size_t n)
{
	while ((int)n >= 0)
	{
		free(s[n]);
		s[n] = NULL;
		n--;
	}
	free(s);
	s = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	count;
	size_t	n;

	result = NULL;
	n = 0;
	count = 0;
	if (!(s))
		return (0);
	count = ft_word_count(s, c);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!(result))
		return (0);
	while (*s && n < count)
	{
		while (*s != '\0' && *s == c)
			s++;
		result[n] = ft_substr(s, 0, ft_letter_count(s, c));
		if (!(result[n]))
			ft_mem_free(result, n);
		n++;
		s = s + ft_letter_count(s, c);
	}
	result[n] = NULL;
	return (result);
}
