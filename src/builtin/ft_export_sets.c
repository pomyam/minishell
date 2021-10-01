/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_sets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:32:02 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/16 20:34:36 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	move_dir(char **line, char *buf, int i)
{
	int		index;
	char	*tmp;
	char	*tmp1;

	if (chdir(line[1]) == -1)
		ft_errors(0);
	if (!getcwd(buf, PATH_MAX))
		ft_errors(0);
	tmp = ft_strjoin("PWD=", buf);
	free(g_msh.env_copy[i]);
	g_msh.env_copy[i] = ft_strdup(tmp);
	free(tmp);
	if (find_in_dop("PWD", &g_msh) != 1)
	{
		index = find_in_dop("PWD", &g_msh);
		tmp = ft_strjoin("declare -x PWD=\"", buf);
		tmp1 = ft_strjoin(tmp, "\"");
		free(g_msh.dop[index]);
		g_msh.dop[index] = ft_strdup(tmp1);
		free(tmp1);
		free(tmp);
	}
}

void	check_dop(char *line)
{
	char	*str;

	if (find_in_dop(line, &g_msh) != -1)
	{
		str = ft_strjoin("declare -x ", line);
		free(g_msh.dop[find_in_dop(line, &g_msh)]);
		g_msh.dop[find_in_dop(line, &g_msh)] = ft_strdup(str);
		free(str);
	}
	else
	{
		str = ft_strjoin("declare -x ", line);
		g_msh.dop = add_to_array(g_msh.dop, str);
		free(str);
	}
}

int	set_variables(char **line, int j)
{
	int		i;

	i = -1;
	while (line[j][++i])
	{
		if (i == 0 && (ft_isalpha(line[j][i + 1]))
			&& (ft_isdigit(line[j][i]) && line[j][i] != '_'))
		{
			write(2, "export: not an identifier: ",
				ft_strlen("export: not an identifier: "));
			write(2, line[j], ft_strlen(line[j]));
			write(2, "\n", 1);
			g_msh.exit_status = 1;
			return (1);
		}
	}
	check_dop(line[j]);
	g_msh.exit_status = 0;
	return (0);
}

void	set_expressions(char *line, int i)
{
	char	*asd;

	if (g_msh.flag == 1)
		asd = ft_substr(line, 0, i - 1);
	else
		asd = ft_substr(line, 0, i);
	ft_work_in_env(asd, line);
	free(asd);
}
