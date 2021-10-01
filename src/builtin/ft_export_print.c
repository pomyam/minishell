/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 22:17:20 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/16 20:33:01 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_quotation(char *str1, int i, int j, int k)
{
	if (str1[++j] != '\"')
		str1[j] = '\"';
	while (g_msh.dop[i][++k])
	{
		if (g_msh.dop[i][k] == '\"')
			continue ;
		else
			str1[++j] = g_msh.dop[i][k];
	}
	if (str1[++j] != '\"')
		str1[j] = '\"';
	str1[++j] = '\0';
	free(g_msh.dop[i]);
	g_msh.dop[i] = ft_strdup(str1);
	return (str1);
}

void	ft_eq(int i)
{
	int		j;
	int		k;
	char	*str1;

	k = 0;
	while (g_msh.dop[++i])
	{
		str1 = (char *)malloc(sizeof(char) * (ft_strlen(g_msh.dop[i]) + 3));
		j = -1;
		while (g_msh.dop[i][++j])
		{
			str1[j] = g_msh.dop[i][j];
			if (g_msh.dop[i][j] == '=')
				break ;
		}
		k = j;
		if (j == (int)ft_strlen(g_msh.dop[i]))
			str1 = NULL;
		else
			str1 = make_quotation(str1, i, j, k);
		free(str1);
	}
}

void	ft_print_export(t_msh g_msh)
{
	int		i;
	int		p;
	char	*tmp;

	i = -1;
	while (g_msh.dop[++i])
	{
		p = i;
		while (g_msh.dop[++p])
		{
			if (ft_cmp(g_msh.dop[i], g_msh.dop[p]) > 0)
			{
				tmp = g_msh.dop[i];
				g_msh.dop[i] = g_msh.dop[p];
				g_msh.dop[p] = tmp;
			}
		}
	}
	ft_eq(-1);
	p = -1;
	while (g_msh.dop[++p])
		printf("%s\n", g_msh.dop[p]);
}

void	ft_work_with_plus(char *line, char *asd)
{
	char	*tmp;
	char	*str;
	char	*str1;
	char	*str2;

	if (g_msh.flag == 1)
	{
		tmp = ft_sec(line);
		str = ft_strjoin("declare -x ", asd);
		str1 = ft_strjoin(str, "=");
		str2 = ft_strjoin(str1, tmp);
		g_msh.dop = add_to_array(g_msh.dop, str2);
		free(tmp);
		free(str);
		free(str1);
		free(str2);
	}
	else
	{
		tmp = ft_strjoin("declare -x ", line);
		g_msh.dop = add_to_array(g_msh.dop, tmp);
		free(tmp);
	}
}

void	ft_work_in_dop(char *line, char *asd)
{
	int		i;
	char	*tmp;

	if (find_in_dop(asd, &g_msh) != -1)
	{
		i = find_in_dop(asd, &g_msh);
		if (g_msh.flag == 1)
			strjoin_to_str(line, asd, i);
		else
		{
			tmp = ft_strjoin("declare -x ", line);
			free(g_msh.dop[find_in_dop(asd, &g_msh)]);
			g_msh.dop[i] = ft_strdup(tmp);
			free(tmp);
		}
	}
	else
		ft_work_with_plus(line, asd);
}
