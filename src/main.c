/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:39:30 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 15:45:32 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_envp_copy(char **envp, t_msh *g_msh)
{
	int		i;
	int		n;
	char	*str;

	n = 0;
	i = 0;
	while (envp[n] != NULL)
		n++;
	g_msh->env_copy = (char **)malloc(sizeof(char *) * (n + 1));
	g_msh->dop = (char **)malloc(sizeof(char *) * (n + 1));
	if (g_msh->env_copy == NULL || g_msh->dop == NULL)
		return (error_message("Memory error"));
	while (i < n)
	{
		g_msh->env_copy[i] = ft_strdup(envp[i]);
		str = ft_strjoin("declare -x ", envp[i]);
		g_msh->dop[i] = ft_strdup(str);
		free(str);
		i++;
	}
	g_msh->env_copy[i] = NULL;
	g_msh->dop[i] = NULL;
	return (1);
}

void	free_g_msh(t_msh *g_msh)
{
	size_t	i;

	i = 0;
	if (g_msh->mask != NULL)
	{
		free(g_msh->mask);
		g_msh->mask = NULL;
	}	
	if (g_msh->commands != NULL)
	{
		free_table(g_msh->commands);
		g_msh->commands = NULL;
	}
	if (g_msh->coms != NULL)
	{
		while (i < g_msh->word_count)
		{
			free(g_msh->coms[i].content);
			i++;
		}
		free(g_msh->coms);
	}
}

void	give_answer(t_msh *g_msh)
{
	if (g_msh->line != NULL)
		free(g_msh->line);
	free_g_msh(g_msh);
	reinit_msh(g_msh);
}

int	get_request(t_msh *g_msh)
{
	g_msh->line = readline("minishell% ");
	if (g_msh->line == NULL)
	{
		write(2, "exit\n", ft_strlen("exit\n"));
		exit(g_msh->exit_status);
	}
	if (g_msh->line[0] != 0)
		add_history(g_msh->line);
	if (parse_line(g_msh) == -1)
		return (-1);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	init_msh(&g_msh);
	get_envp_copy(envp, &g_msh);
	g_msh.tmp_fd[0] = dup(0);
	g_msh.tmp_fd[1] = dup(1);
	g_msh.flag = 0;
	while (1)
	{
		signal(SIGINT, &ft_signal_in);
		signal(SIGQUIT, &ft_signal_in);
		get_request(&g_msh);
		give_answer(&g_msh);
	}
	return (g_msh.exit_status);
}
