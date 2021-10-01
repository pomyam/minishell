/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 22:17:33 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/16 20:35:29 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_to_table(char **table)
{
	int	i;

	i = -1;
	while (table[++i] != NULL)
		free(table[i]);
	free(table);
}

void	cut_array_g_msh(int index)
{
	int		str_count;
	int		i;
	int		j;
	char	**new;

	str_count = 0;
	i = 0;
	j = -1;
	while (g_msh.env_copy[str_count] != NULL)
		str_count++;
	new = (char **)malloc(sizeof(char *) * (str_count));
	while (i < str_count)
	{
		if (i != index)
			new[++j] = ft_strdup(g_msh.env_copy[i]);
		i++;
	}
	new[++j] = NULL;
	free_to_table(g_msh.env_copy);
	g_msh.env_copy = new;
}

void	cut_array_dop(int index)
{
	int		str_count;
	int		i;
	int		j;
	char	**new;

	str_count = 0;
	i = 0;
	j = -1;
	while (g_msh.dop[str_count] != NULL)
		str_count++;
	new = (char **)malloc(sizeof(char *) * (str_count));
	while (i < str_count)
	{
		if (i != index)
			new[++j] = ft_strdup(g_msh.dop[i]);
		i++;
	}
	new[++j] = NULL;
	free_to_table(g_msh.dop);
	g_msh.dop = new;
}

int	check_errors_u(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if ((ft_isalnum(line[i + 1])
				|| ft_isdigit(line[i + 1])) && ft_isdigit(line[i]))
		{
			write(2, "unset: not an identifier: ",
				ft_strlen("unset: not an identifier: "));
			write(2, line, ft_strlen(line));
			write(2, "\n", 1);
			return (1);
		}
	}
	return (0);
}

int	ft_unset(char **line)
{
	int		j;

	j = 0;
	while (line[++j])
	{
		if (check_errors_u(line[j]) == 1)
			return (1);
		if (find_in_envp(line[j], &g_msh) != -1)
		{
			cut_array_g_msh(find_in_envp(line[j], &g_msh));
			if (find_in_dop(line[j], &g_msh) != -1)
				cut_array_dop(find_in_dop(line[j], &g_msh));
		}
		if (find_in_dop(line[j], &g_msh) != -1)
			cut_array_dop(find_in_dop(line[j], &g_msh));
	}
	return (0);
}
