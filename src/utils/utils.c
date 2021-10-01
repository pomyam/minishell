/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:46:15 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/14 18:10:50 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (-1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	while (str1[i] == str2[i] && str1[i] != '\0')
		i++;
	if (str1[i] != '\0')
		return (-1);
	return (0);
}

int	only_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '	')
			i++;
		else
			return (0);
	}
	return (1);
}

t_exec	*new_exec(void)
{
	t_exec	*new;

	new = (t_exec *)malloc(sizeof(t_exec));
	if (new == NULL)
		return (NULL);
	new->args = NULL;
	new->path = NULL;
	new->fdin = -1;
	new->fdout = -1;
	new->type = -1;
	new->next = NULL;
	new->prev = NULL;
	new->exit_status = -1;
	new->pid = -1;
	new->redir = NULL;
	new->num = -1;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->not_found = -1;
	return (new);
}

t_redir	*new_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->file = NULL;
	redir->type = -1;
	redir->next = NULL;
	return (redir);
}

void	push_back_red(t_redir **head, t_redir *nw)
{
	t_redir	*i;

	if (*head == NULL)
		*head = nw;
	else
	{
		i = *head;
		while (i->next != NULL)
		{
			i = i->next;
		}
		i->next = nw;
	}
}
