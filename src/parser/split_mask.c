/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 14:55:02 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 11:06:51 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_spec(char c)
{
	if (c == PIPE || c == RDIN || c == RDOUT
		|| c == HEREDOC_IN || c == HEREDOC_OUT)
		return (1);
	return (0);
}

static int	ft_word_count(char const *s)
{
	size_t	n;

	n = 0;
	while (*s != '\0')
	{
		while (*s == SPAC)
			s++;
		if (*s != SPAC && *s != '\0' && !is_spec(*s))
			n++;
		while (*s != SPAC && *s != '\0' && !is_spec(*s))
			s++;
		if (is_spec(*s))
		{
			n++;
			if (*s == HEREDOC_OUT || *s == HEREDOC_IN)
				s += 2;
			else
				s++;
		}
	}
	return (n);
}

static int	ft_letter_count(char const *s, char const *mask)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 1;
	if (is_spec(*mask))
	{
		if (*mask == HEREDOC_OUT || *mask == HEREDOC_IN)
			i++;
		mask++;
		s++;
		return (i);
	}
	while (*mask != SPAC && *s != '\0' && !is_spec(*mask))
	{
		s++;
		mask++;
		n++;
	}
	return (n);
}

int	split_with_mask(t_msh *g_msh)
{
	size_t	n;
	char	*line;
	char	*mask;

	line = g_msh->line;
	mask = g_msh->mask;
	n = 0;
	g_msh->word_count = ft_word_count(mask);
	g_msh->commands = (char **)malloc((g_msh->word_count + 1) * sizeof(char *));
	if (g_msh->commands == NULL)
		return (error_message("Memory error"));
	return (split_msh(g_msh, line, mask, n));
}

int	split_msh(t_msh *g_msh, char *line, char *mask, size_t n)
{
	size_t	i;

	while (*line && n < g_msh->word_count)
	{
		while (*line != '\0' && *mask == SPAC)
		{
			line++;
			mask++;
		}		
		g_msh->commands[n++] = ft_substr(line, 0, ft_letter_count(line, mask));
		if (!(g_msh->commands[n - 1]))
			return (error_message("Memory error"));
		i = ft_letter_count(line, mask);
		line = line + i;
		mask = mask + i;
	}
	g_msh->commands[n] = NULL;
	return (1);
}
