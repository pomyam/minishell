/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:27:23 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 20:52:21 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_rdin(t_redir *red, t_exec *now)
{
	if (now->fdin != -1)
		close(now->fdin);
	now->fdin = open(red->file, O_RDONLY);
	if (now->fdin == -1)
		return (message_errno(errno, red->file));
	return (1);
}

int	handle_rdout(t_redir *red, t_exec *now)
{
	if (now->fdout != -1)
		close(now->fdout);
	now->fdout = open(red->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (now->fdout == -1)
		return (message_errno(errno, red->file));
	return (1);
}

int	handle_hdout(t_redir *red, t_exec *now)
{
	if (now->fdout != -1)
		close(now->fdout);
	now->fdout = open(red->file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (now->fdout == -1)
		return (message_errno(errno, red->file));
	return (1);
}

int	do_heredoc(t_exec *now, t_redir *red)
{
	char	*line;
	int		fd[2];

	line = NULL;
	if (now->fdin != -1)
		close(now->fdin);
	if (pipe(fd) == -1)
		return (error_message("Heredoc fail"));
	now->fdin = fd[1];
	while (ft_strcmp(line, red->file) != 0)
	{
		line = readline("> ");
		if (ft_strcmp(line, red->file) == 0 || line == 0)
		{
			close(fd[1]);
			free(line);
			break ;
		}
		ft_putendl_fd(line, now->fdin);
		free(line);
	}
	now->fdin = fd[0];
	return (1);
}

int	handle_redirect(t_exec *now)
{
	t_redir	*red;

	red = now->redir;
	while (red != NULL)
	{
		if (red->type == RDIN)
			if (handle_rdin(red, now) == -1)
				return (-1);
		if (red->type == RDOUT)
			if (handle_rdout(red, now) == -1)
				return (-1);
		if (red->type == HEREDOC_OUT)
			if (handle_hdout(red, now) == -1)
				return (-1);
		if (red->type == HEREDOC_IN)
			if (do_heredoc(now, red) == -1)
				return (-1);
		red = red->next;
	}
	return (1);
}
