/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:36:27 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/15 19:58:10 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **line, int length)
{
	int	i;

	i = 1;
	if (line[0] && !line[1])
		printf("\n");
	else
	{
		while (ft_strcmp(line[i], "-n") == 0)
			i++;
		while (line[i])
		{
			write(1, line[i], ft_strlen(line[i]));
			if (i != length - 1)
			{
				if (ft_strlen(line[i + 1]) != 0 && line[i][0] != '\0')
					write(1, " ", 1);
			}
			i++;
		}
		if (ft_strcmp("-n", line[1]) != 0)
			write(1, "\n", 1);
	}
	g_msh.exit_status = 0;
	return (0);
}
