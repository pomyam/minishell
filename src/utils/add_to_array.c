/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:23:02 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/16 20:22:35 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i] != NULL)
	{
		free(table[i]);
		i++;
	}
	free(table);
	return (1);
}

char	**add_to_array(char **table, char *str)
{
	int		str_count;
	int		i;
	char	**copy;
	char	**new;

	if (table == NULL)
	{
		table = (char **)malloc(sizeof(char *) * 1);
		*table = NULL;
	}
	copy = table;
	str_count = 0;
	i = 0;
	while (copy[str_count] != NULL)
		str_count++;
	new = (char **)malloc(sizeof(char *) * (str_count + 2));
	while (i < str_count)
	{
		new[i] = ft_strdup(copy[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free_table(copy);
	return (new);
}

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(str, "cd") == 0)
		return (CD);
	if (ft_strcmp(str, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(str, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(str, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(str, "env") == 0)
		return (ENV);
	if (ft_strcmp(str, "exit") == 0)
		return (EXIT);
	return (-1);
}
