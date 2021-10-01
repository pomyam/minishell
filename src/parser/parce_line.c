/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:41:22 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 11:05:33 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_mask(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (RDIN);
	else if (c == '>')
		return (RDOUT);
	else if (c == ' ' || c == '	')
		return (SPAC);
	else if (c == '\'')
		return (QUOTE);
	else if (c == '\"')
		return (DOUBLEQUOTE);
	else if (c == '$')
		return (DOLLAR);
	return (OTHER);
}

int	find_heredoc(t_msh *g_msh)
{
	int	i;

	i = 0;
	while (g_msh->mask[i] != '\0')
	{
		if (g_msh->mask[i] == RDIN && g_msh->mask[i + 1] == RDIN)
		{
			g_msh->mask[i] = HEREDOC_IN;
			g_msh->mask[i + 1] = HEREDOC_IN;
		}
		if (g_msh->mask[i] == RDOUT && g_msh->mask[i + 1] == RDOUT)
		{
			g_msh->mask[i] = HEREDOC_OUT;
			g_msh->mask[i + 1] = HEREDOC_OUT;
		}
		i++;
	}
	return (1);
}

int	make_mask(t_msh *g_msh)
{
	int	i;

	i = 0;
	g_msh->mask = (char *)malloc(sizeof(char) * (ft_strlen(g_msh->line) + 1));
	if (g_msh->mask == NULL)
		return (error_message("Memory error"));
	while (g_msh->line[i] != '\0')
	{
		g_msh->mask[i] = get_mask(g_msh->line[i]);
		i++;
	}
	g_msh->mask[i] = '\0';
	find_heredoc(g_msh);
	return (1);
}

int	parse_line(t_msh *g_msh)
{
	if (ft_strlen(g_msh->line) == 0 || only_spaces(g_msh->line))
		return (1);
	if (make_mask(g_msh) == -1)
		return (-1);
	if (make_commands(g_msh) == -1)
		return (-1);
	return (1);
}
