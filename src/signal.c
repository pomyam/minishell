/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 22:16:52 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/15 20:52:47 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_out(int code)
{
	char	*str;

	if (code == SIGQUIT)
	{
		str = ft_itoa(code);
		write(2, "Quit: ", ft_strlen("Quit: "));
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		free(str);
		kill(g_msh.sig.pid, SIGQUIT);
	}
	else if (code == SIGINT)
	{
		write(2, "\n", 1);
		kill(g_msh.sig.pid, SIGINT);
	}
}

void	ft_signal_in(int code)
{
	if (code == SIGINT)
	{
		rl_redisplay();
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \b\b\n", 6);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_msh.cost = 1;
	}
	else if (code == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \b\b", 5);
	}
}
