/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:47:30 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:12:18 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*n_pointer(char *line)
{
	char	*n_pointer;
	char	*tmp;

	n_pointer = NULL;
	tmp = NULL;
	if (line)
	{
		tmp = line;
		while (*tmp != '\0')
		{
			if (*tmp == '\n')
			{
				n_pointer = tmp;
				return (n_pointer);
			}
			tmp++;
		}
	}
	return (NULL);
}

static int	ft_get_line(char **line, char **cache)
{
	char	*tmp;
	char	*separator;

	separator = NULL;
	tmp = NULL;
	separator = n_pointer(*cache);
	if (separator != NULL)
	{
		*separator = '\0';
		free(*line);
		*line = ft_strdup(*cache);
		separator++;
		tmp = *cache;
		*cache = ft_strdup(separator);
		free(tmp);
	}
	else
	{
		free(*line);
		*line = ft_strdup(*cache);
		free(*cache);
		*cache = NULL;
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	t_gnl		gnl;
	static char	*cache;

	gnl.buf = (char *)malloc(BUFFER_SIZE + 1);
	if ((BUFFER_SIZE <= 0) || (fd < 0) || (!line) || (!(gnl.buf)))
		return (-1);
	*line = NULL;
	gnl.read_count = 1;
	if (!cache)
		cache = ft_strnew(1);
	while (!(n_pointer(cache)) && (gnl.read_count))
	{
		gnl.read_count = read(fd, gnl.buf, BUFFER_SIZE);
		if (gnl.read_count == -1)
			return (-1);
		gnl.buf[gnl.read_count] = '\0';
		gnl.tmp = cache;
		cache = ft_strjoin(cache, gnl.buf);
		free(gnl.tmp);
	}
	ft_get_line(line, &cache);
	free(gnl.buf);
	if (gnl.read_count == 0)
		return (0);
	return (1);
}
