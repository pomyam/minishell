/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 22:17:00 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/16 20:35:18 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_in_envp(char *line, char *asd)
{
	int		i;
	char	*tmp;
	char	*str;

	i = find_in_envp(asd, &g_msh);
	if (g_msh.flag == 1)
	{
		tmp = ft_sec(line);
		str = ft_strjoin(g_msh.env_copy[find_in_envp(asd, &g_msh)], tmp);
		free(g_msh.env_copy[find_in_envp(asd, &g_msh)]);
		g_msh.env_copy[i] = ft_strdup(str);
		free(str);
		free(tmp);
	}
	else
	{
		free(g_msh.env_copy[find_in_envp(asd, &g_msh)]);
		g_msh.env_copy[i] = ft_strdup(line);
	}
	ft_work_in_dop(line, asd);
}

void	ft_work_in_env(char *asd, char *line)
{
	char	*tmp;
	char	*str;
	char	*str1;

	if (find_in_envp(asd, &g_msh) != -1)
		change_in_envp(line, asd);
	else
	{
		if (g_msh.flag == 1)
		{
			tmp = ft_sec(line);
			str = ft_strjoin(asd, "=");
			str1 = ft_strjoin(str, tmp);
			g_msh.env_copy = add_to_array(g_msh.env_copy, str1);
			free(tmp);
			free(str1);
			free(str);
		}
		else
			g_msh.env_copy = add_to_array(g_msh.env_copy, line);
		ft_work_in_dop(line, asd);
	}
}

int	check_errors(char *line)
{
	int	i;

	i = -1;
	g_msh.flag = 0;
	while (line[++i] != '=' && i < (int)ft_strlen(line))
	{
		if (line[i] == '+' && line[i + 1] == '=')
			g_msh.flag = 1;
		else if (!ft_isalpha(line[i]) && !ft_isdigit(line[i])
			&& line[i] != '_')
			return (-1);
		else if (i == 0 && (ft_isalpha(line[i + 1]) || ft_isdigit(line[i + 1]))
			&& (ft_isdigit(line[i]) && line[i] != '_'))
			return (-1);
	}
	if (ft_strcmp(line, "=") == 0)
		return (-1);
	return (i);
}

int	ft_export(char **line)
{
	int	i;
	int	j;

	if (line[0] && !line[1])
		ft_print_export(g_msh);
	else
	{
		j = 0;
		while (line[++j])
		{
			i = check_errors(line[j]);
			if (i == -1)
				return (ft_print_error(line[j]));
			if (i < (int)ft_strlen(line[j]))
				set_expressions(line[j], i);
			else
			{
				if (set_variables(line, j) == 1)
					return (1);
			}
		}
	}
	return (0);
}
