/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:34:03 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/16 20:33:30 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmp(char *s1, char *s2)
{
	const unsigned char	*s;
	const unsigned char	*p;

	s = (const unsigned char *)s1;
	p = (const unsigned char *)s2;
	if (!s && !p)
		return (0);
	while ((*s == *p) && *s)
	{
		s++;
		p++;
	}
	return (*s - *p);
}

char	*ft_first(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '=' && line[i])
		i++;
	j = -1;
	str = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (line[++i] != '=' && line[i])
		str[++j] = line[i];
	str[++j] = '\0';
	return (str);
}

char	*ft_sec(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '=' && line[i])
		i++;
	j = -1;
	if ((int)ft_strlen(line) == i)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(line) - i));
	while (line[++i] && line[i])
		str[++j] = line[i];
	str[++j] = '\0';
	return (str);
}

int	ft_print_error(char *str)
{
	write(2, "minishell: export: `", ft_strlen("minishell: export: `"));
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier: ",
		ft_strlen("': not a valid identifier: "));
	write(2, "\n", 1);
	g_msh.exit_status = 1;
	return (1);
}
