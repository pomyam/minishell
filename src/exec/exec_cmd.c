/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:25:51 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/16 20:20:05 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_exec(t_exec *head)
{
	if (handle_redirect(head) == -1)
		return (-1);
	if (head->args == NULL)
		return (-1);
	return (1);
}

int	error_signal(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		else if (WTERMSIG(status) == 3)
			return (131);
	}
	return (WEXITSTATUS(status));
}

int	handle_exit_status(int status, t_exec *head)
{
	if (status == 0 || status == 1)
		return (1);
	else if (status == EACCES)
	{
		g_msh.exit_status = 126;
		printf("minishell: %s: %s\n", head->path, strerror(status));
	}
	else if (status == 127)
	{
		g_msh.exit_status = 127;
		printf("minishell: %s: command not found\n", head->path);
	}
	else if (status == ENOENT)
	{
		g_msh.exit_status = 127;
		printf("minishell: %s: %s\n", head->path, strerror(status));
	}
	else if (status != 0)
		g_msh.exit_status = status;
	return (1);
}

int	do_parent(t_exec *head)
{
	signal(SIGINT, &ft_signal_out);
	signal(SIGQUIT, &ft_signal_out);
	waitpid(head->pid, &head->exit_status, 0);
	return (1);
}

int	exec_simple_cmd(t_exec *head)
{
	int	fd[2];

	if (prepare_exec(head) == -1)
		return (-1);
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (head->fdin != -1)
		dup2(head->fdin, 0);
	if (head->fdout != -1)
		dup2(head->fdout, 1);
	if (is_builtin(head->args[0]) != -1)
		return (do_builtin(head));
	head->pid = fork();
	g_msh.sig.pid = head->pid;
	if (head->pid == 0)
		do_execve(head);
	else
		do_parent(head);
	g_msh.exit_status = error_signal(head->exit_status);
	handle_exit_status(g_msh.exit_status, head);
	dup2(fd[0], 0);
	dup2(fd[0], 1);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
