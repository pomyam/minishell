/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:47:33 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 10:39:31 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	get_type(const char *s)
{
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	if (ft_strcmp(s, "<") == 0)
		return (RDIN);
	if (ft_strcmp(s, ">") == 0)
		return (RDOUT);
	if (ft_strcmp(s, "<<") == 0)
		return (HEREDOC_IN);
	if (ft_strcmp(s, ">>") == 0)
		return (HEREDOC_OUT);
	return (WORD);
}

int	get_command_info(t_msh *g_msh)
{
	size_t	i;

	i = 0;
	g_msh->coms = (t_command *)malloc(sizeof(t_command) * (g_msh->word_count));
	if (g_msh->coms == NULL)
		return (error_message("Memory error"));
	while (i < g_msh->word_count)
	{
		g_msh->coms[i].type = get_type(g_msh->commands[i]);
		g_msh->coms[i].num = i;
		g_msh->coms[i].content = ft_strdup(g_msh->commands[i]);
		i++;
	}
	return (1);
}

int	find_doublequotes(int i)
{
	i++;
	while (g_msh.mask[i] != DOUBLEQUOTE && g_msh.mask[i] != '\0')
	{
		if (g_msh.mask[i] != DOLLAR)
			g_msh.mask[i] = OTHER;
		i++;
	}
	if (g_msh.mask[i] == '\0')
		return (error_message("minishell: Syntax error: please close quotes"));
	return (i);
}

int	find_quotes(t_msh *g_msh)
{
	int	i;

	i = 0;
	while (g_msh->mask[i] != '\0')
	{
		if (g_msh->mask[i] == QUOTE)
		{
			i++;
			while (g_msh->mask[i] != QUOTE && g_msh->mask[i] != '\0')
			{
				g_msh->mask[i] = OTHER;
				i++;
			}
			if (g_msh->mask[i] == '\0')
				return (error_message("minishell: Syntax error: quotes"));
		}
		if (g_msh->mask[i] == DOUBLEQUOTE)
			i = find_doublequotes(i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	make_commands(t_msh *g_msh)
{
	if (find_quotes(g_msh) == -1)
		return (-1);
	split_with_mask(g_msh);
	if (get_command_info(g_msh) == -1)
		return (-1);
	if (start_exec(g_msh) == -1)
		return (-1);
	return (1);
}
