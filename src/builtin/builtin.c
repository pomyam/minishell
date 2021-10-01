/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 13:30:57 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/15 11:04:00 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmp_in_dop(char *tmp, char *env)
{
	char	*env_part;
	int		len;

	len = 0;
	while (env[len] != '=' && env[len] != '\0')
		len++;
	env_part = ft_substr(env, 0, len);
	if (ft_strcmp(tmp, env_part) == 0)
	{
		free(env_part);
		return (0);
	}
	free(env_part);
	return (1);
}

int	find_in_dop(char *str, t_msh *g_msh)
{
	int		i;
	char	*tmp;
	char	*first;

	i = 0;
	first = ft_first(str);
	tmp = ft_strjoin("declare -x ", str);
	while (g_msh->dop[i])
	{
		if (cmp_in_dop(tmp, g_msh->dop[i]) == 0)
		{
			free(tmp);
			free(first);
			return (i);
		}
		i++;
	}
	free(first);
	free(tmp);
	return (-1);
}

int	ft_errors(int l)
{
	int	i;

	i = -1;
	while (strerror(errno)[++i])
		ft_putchar_fd(strerror(errno)[i], 2);
	ft_putchar_fd('\n', 2);
	if (l == 1)
		g_msh.exit_status = 127;
	else
		g_msh.exit_status = 1;
	return (1);
}

int	ft_pwd(int unnes)
{
	char	*buf;

	(void)unnes;
	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!buf)
		printf("Can't make buf!\n");
	if (!getcwd(buf, PATH_MAX))
		return (ft_errors(-1));
	printf("%s\n", buf);
	free(buf);
	g_msh.exit_status = 0;
	return (0);
}

void	build_in(char **line)
{
	int		i;
	int		length;

	i = -1;
	length = 0;
	while (line[++i])
		length++;
	if (ft_strcmp(line[0], "echo") == 0)
		ft_echo(line, length);
	else if (ft_strcmp(line[0], "pwd") == 0)
		ft_pwd(length);
	else if (ft_strcmp(line[0], "cd") == 0)
		ft_cd(line);
	else if (ft_strcmp(line[0], "export") == 0)
		ft_export(line);
	else if (ft_strcmp(line[0], "unset") == 0)
		ft_unset(line);
	else if (ft_strcmp(line[0], "env") == 0)
		ft_env(-1);
	else if (ft_strcmp(line[0], "exit") == 0)
		ft_exit(line);
	else if (ft_strcmp(line[0], "\n"))
		printf("\n");
	else
		ft_errors(1);
}
