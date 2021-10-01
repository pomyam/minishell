/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:20:33 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/16 20:32:43 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_execve(t_exec *head)
{
	if (head->not_found == 1)
		exit(127);
	if (execve(head->path, head->args, g_msh.env_copy) != 0)
		exit(errno);
}

void	get_fd(t_exec *head, int fd_in, int fd_out)
{
	int		fd[2];
	pid_t	pid;

	pid = 0;
	if (head->prev)
	{
		if (pipe(fd) == -1)
			message_errno(errno, "");
		fd_in = fd[0];
		pid = fork();
		g_msh.sig.pid = pid;
		if (!pid)
		{
			close(fd[0]);
			get_fd(head->prev, dup(g_msh.tmp_fd[0]), fd[1]);
			exit(errno);
		}
		close(fd[1]);
	}
	exec_cmd(fd_in, fd_out, head, pid);
}

int	exec_scmd_pipe(t_exec *head)
{
	if (prepare_exec(head) == -1)
		return (-1);
	if (head->fdin != -1)
		dup2(head->fdin, 0);
	if (head->fdout != -1)
		dup2(head->fdout, 1);
	if (is_builtin(head->args[0]) != -1)
	{
		do_builtin(head);
		exit(g_msh.exit_status);
	}
	do_execve(head);
	return (1);
}

int	handle_estatus(int status, t_exec *head)
{
	if (status == 0 || status == 1)
		return (1);
	else if (status == EACCES)
		printf("minishell: %s: is a directory\n", head->path);
	else if (status == 127)
		printf("minishell: %s: command not found\n", head->path);
	else if (status == ENOENT)
		printf("minishell: %s: no such file or directory\n", head->path);
	return (1);
}

int	exec_cmd(int fd_in, int fd_out, t_exec *head, pid_t pid)
{
	pid_t	pid2;

	pid2 = fork();
	if (!pid2)
	{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		exec_scmd_pipe(head);
		do_parent(head);
		exit(head->exit_status);
	}
	if (fd_in != 0)
		close (fd_in);
	if (fd_out != 1)
		close (fd_out);
	if (pid)
		waitpid(pid, 0, 0);
	if (pid2)
		waitpid(pid2, &head->exit_status, 0);
	if (head->next)
		handle_estatus(WEXITSTATUS(head->exit_status), head);
	return (1);
}
