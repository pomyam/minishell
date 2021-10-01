/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:45:55 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/16 20:19:38 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	take_com(t_exec *exec, char *com)
{
	exec->path = ft_strdup(com);
	exec->not_found = 1;
	return (1);
}

int	look_for_bin(t_exec *exec, char **paths, char *com)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp2 = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(tmp2, com);
		if (open(tmp, O_RDONLY) != -1)
		{
			exec->path = ft_strdup(tmp);
			free(tmp);
			free(tmp2);
			return (1);
		}
		free(tmp);
		free(tmp2);
		i++;
	}
	if (paths[i] == NULL)
		take_com(exec, com);
	return (1);
}

int	find_bin(char *com, char **paths, t_exec *exec)
{
	if (contains_slash(com) == 1)
	{
		exec->path = ft_strdup(com);
		return (1);
	}
	look_for_bin(exec, paths, com);
	return (1);
}

int	prep_fd(t_exec *tmp)
{
	while (tmp->next)
		tmp = tmp->next;
	get_fd(tmp, 0, 1);
	g_msh.exit_status = error_signal(tmp->exit_status);
	handle_exit_status(g_msh.exit_status, tmp);
	return (1);
}

int	start_exec(t_msh *g_msh)
{
	t_exec	*head;
	t_exec	*tmp;

	tmp = NULL;
	head = new_exec();
	tmp = head;
	if (parse_execs(g_msh, &tmp) == -1)
	{
		free_exec(head);
		return (-1);
	}
	if (tmp->next == NULL)
	{
		if (exec_simple_cmd(tmp) == -1)
		{
			free_exec(head);
			return (-1);
		}
	}
	else
		prep_fd(tmp);
	free_exec(head);
	return (1);
}
