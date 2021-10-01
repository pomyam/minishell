/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:19:56 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/16 20:34:20 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exist_oldpwd(char *buf)
{
	char	*tmp;
	int		i;

	i = find_in_envp("OLDPWD", &g_msh);
	tmp = ft_strjoin("OLDPWD=", buf);
	free(g_msh.env_copy[find_in_envp("OLDPWD", &g_msh)]);
	g_msh.env_copy[i] = ft_strdup(tmp);
	free(tmp);
	i = find_in_dop("OLDPWD", &g_msh);
	if (find_in_dop("OLDPWD", &g_msh) != -1)
	{
		tmp = ft_strjoin("declare -x OLDPWD=", buf);
		free(g_msh.dop[find_in_dop("OLDPWD", &g_msh)]);
		g_msh.dop[i] = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin("declare -x OLDPWD=", buf);
		g_msh.dop = add_to_array(g_msh.dop, tmp);
		free(tmp);
	}
}

void	edit_pwd(char *buf)
{
	char	*tmp;
	int		i;

	if (find_in_envp("OLDPWD", &g_msh) != -1)
		exist_oldpwd(buf);
	else
	{
		tmp = ft_strjoin("OLDPWD=", buf);
		g_msh.env_copy = add_to_array(g_msh.env_copy, tmp);
		free(tmp);
		i = find_in_dop("OLDPWD", &g_msh);
		if (find_in_dop("OLDPWD", &g_msh) != -1)
		{
			tmp = ft_strjoin("declare -x OLDPWD=", buf);
			free(g_msh.dop[find_in_dop("OLDPWD", &g_msh)]);
			g_msh.dop[i] = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			tmp = ft_strjoin("declare -x OLDPWD=", buf);
			g_msh.dop = add_to_array(g_msh.dop, tmp);
			free(tmp);
		}
	}
}

void	work_with_no_param(char *str)
{
	int		j;
	char	*tmp;
	char	*tmp1;

	if (find_in_dop("PWD", &g_msh) != 1)
	{
		j = find_in_dop("PWD", &g_msh);
		tmp = ft_strjoin("declare -x PWD=\"", str);
		tmp1 = ft_strjoin(tmp, "\"");
		free(g_msh.dop[j]);
		g_msh.dop[j] = ft_strdup(tmp1);
		free(tmp1);
		free(tmp);
	}
}

void	edit_oldpwd(char **line, char *buf, char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_msh.env_copy[++i] != NULL)
	{
		if (ft_strncmp(g_msh.env_copy[i], "PWD=", 4) == 0)
		{
			edit_pwd(buf);
			if (line[1] == NULL)
			{
				if (chdir(str) == -1)
					ft_errors(0);
				tmp = ft_strjoin("PWD=", str);
				free(g_msh.env_copy[i]);
				g_msh.env_copy[i] = ft_strdup(tmp);
				free(tmp);
				work_with_no_param(str);
			}
			else
				move_dir(line, buf, i);
		}
	}
}

int	ft_cd(char **line)
{
	char	*buf;
	char	*str;
	int		i;

	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!buf)
		printf("Can't make buf!\n");
	if (!getcwd(buf, PATH_MAX))
		return (ft_errors(0));
	i = -1;
	while (g_msh.env_copy[++i])
	{
		if (ft_strncmp(g_msh.env_copy[i], "HOME=", 5) == 0)
			str = ft_sec(g_msh.env_copy[i]);
	}
	edit_oldpwd(line, buf, str);
	free(str);
	free(buf);
	return (0);
}
