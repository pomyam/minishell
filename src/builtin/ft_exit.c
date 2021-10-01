/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 16:12:33 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/16 20:35:04 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned long long	ft_atoi_long(const char *str)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		 || *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	exit_for_export(char *line)
{
	int		i;
	char	*str;

	i = -1;
	str = "minishell: export: ";
	while (++i < (int)ft_strlen(str))
		ft_putchar_fd(str[i], 2);
	ft_putchar_fd('`', 2);
	i = -1;
	while (++i < (int)ft_strlen(line))
		ft_putchar_fd(line[i], 2);
	ft_putchar_fd('\'', 2);
}

int	exit_error(char *line, int num)
{
	int		i;
	char	*str;

	i = -1;
	if (num == 1)
	{
		str = "minishell: exit: ";
		while (++i < (int)ft_strlen(str))
			ft_putchar_fd(str[i], 2);
		i = -1;
		while (++i < (int)ft_strlen(line))
			ft_putchar_fd(line[i], 2);
		str = ": numeric argument required";
	}
	i = -1;
	while (++i < (int)ft_strlen(str))
		ft_putchar_fd(str[i], 2);
	ft_putchar_fd('\n', 2);
	g_msh.exit_status = 1;
	return (g_msh.exit_status);
}

void	check_alpha(char **line)
{
	int	i;
	int	j;

	i = 0;
	while (line[++i])
	{
		j = -1;
		while (line[i][++j])
		{
			if (ft_isalpha(line[i][j]))
			{
				exit_error(line[i], 1);
				g_msh.exit_status = 255;
				break ;
			}
		}
	}
}

void	ft_exit(char **line)
{
	printf("exit\n");
	if (line[1] && line[2])
		exit_error(line[1], 1);
	else if (line[1] && !line[2])
	{
		if (ft_strcmp(line[1], "-9223372036854775808") == 0)
			g_msh.exit_status = 0;
		else if ((int)ft_atoi_long(line[1]) == -1)
			g_msh.exit_status = 255;
		else if (ft_atoi_long(line[1]) < 256 && line[1][0] == '-')
			g_msh.exit_status = 256 - ft_atoi_long(line[1]);
		else if (ft_atoi_long(line[1]) > 255
			&& ft_atoi_long(line[1]) < LLONG_MAX)
			g_msh.exit_status = ft_atoi_long(line[1]) % 256;
		else if (ft_atoi_long(line[1]) >= LLONG_MAX)
			g_msh.exit_status = 255;
		else if (ft_atoi_long(line[1]) > 0)
			g_msh.exit_status = ft_atoi_long(line[1]) % 256;
		else
			g_msh.exit_status = 0;
		check_alpha(line);
	}
	exit(g_msh.exit_status);
}
