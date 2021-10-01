/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:48:47 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 11:08:21 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reinit_msh(t_msh *g_msh)
{
	g_msh->line = NULL;
	g_msh->mask = NULL;
	g_msh->commands = NULL;
	g_msh->word_count = 0;
	g_msh->coms = NULL;
	g_msh->flag = 0;
	g_msh->cost = 0;
	g_msh->count = 0;
}

void	init_msh(t_msh *g_msh)
{
	g_msh->env_copy = NULL;
	g_msh->dop = NULL;
	g_msh->line = NULL;
	g_msh->mask = NULL;
	g_msh->commands = NULL;
	g_msh->word_count = 0;
	g_msh->coms = NULL;
	g_msh->exit_status = 0;
	g_msh->count = 0;
	g_msh->cost = 0;
}

void	init_quotes(t_quotes *q, char **com)
{
	q->oq = 0;
	q->dq = 0;
	q->copy = *com;
	q->result = NULL;
	q->i = 0;
}
