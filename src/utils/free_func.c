/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:30:32 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 17:51:47 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;
	t_redir	*t;

	tmp = redir;
	while (tmp != NULL)
	{
		if (tmp->file != NULL)
			free(tmp->file);
		tmp = tmp->next;
	}
	tmp = redir;
	while (tmp != NULL)
	{
		t = tmp->next;
		free(tmp);
		tmp = t;
	}
}

int	free_exec(t_exec *head)
{
	t_exec	*tmp;
	t_exec	*t;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->args != NULL)
			free_table(tmp->args);
		if (tmp->path != NULL)
			free(tmp->path);
		if (tmp->redir != NULL)
			free_redir(tmp->redir);
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp != NULL)
	{
		t = tmp->next;
		free(tmp);
		tmp = t;
	}
	return (1);
}
