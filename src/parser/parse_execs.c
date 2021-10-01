/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:39:32 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 17:52:33 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_to_structure(t_exec **head, char **extend, int i)
{
	t_exec	*tmp;

	tmp = *head;
	while (extend[i] != NULL)
	{
		while (extend[i] != NULL && ft_strcmp(extend[i], "|") != 0
			&& is_redir(extend[i]) == 0)
			tmp->args = add_to_array(tmp->args, extend[i++]);
		if (extend[i] == NULL)
			break ;
		if (is_redir(extend[i]) == 1)
		{
			if (add_to_redir(extend, &i, tmp) == -1)
				return (-1);
			continue ;
		}
		if (ft_strcmp(extend[i], "|") == 0)
		{
			tmp->next = new_exec();
			tmp->next->prev = tmp;
			tmp = tmp->next;
			i++;
		}
	}
	return (1);
}

int	get_path(char *com, char **env, t_exec *exec)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = 0;
	if (ft_strcmp(com, "") == 0)
		return (-1);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
	{
		exec->path = ft_strdup(com);
		return (1);
	}
	tmp = env[i] + 5;
	paths = ft_split(tmp, ':');
	if (find_bin(com, paths, exec) == -1)
		return (-1);
	if (paths != NULL)
		free_table(paths);
	return (1);
}

int	find_path(t_exec **head, char **env_copy)
{
	t_exec	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (tmp->args == NULL)
			return (-1);
		if (is_builtin(tmp->args[0]) == -1)
			if (get_path(tmp->args[0], env_copy, tmp) == -1)
				return (-1);
		tmp = tmp->next;
	}
	return (1);
}

int	check_parsed(char **extend)
{
	size_t	i;

	i = 0;
	while (extend[i] != NULL)
	{
		if (i == 0 && ft_strcmp(extend[i], "|") == 0)
			return (error_message("minishell: Syntax error: pipe"));
		if (i == g_msh.word_count - 1 && ft_strcmp(extend[i], "|") == 0)
			return (error_message("minishell: Syntax error: pipe"));
		if (ft_strcmp(extend[i], "|") == 0
			&& ft_strcmp(extend[i + 1], "|") == 0)
			return (error_message("minishell: Syntax error: pipe"));
		if (is_redir(extend[i]) && is_redir(extend[i + 1]))
			return (error_message("minishell: Syntax error: redirect"));
		if (i == g_msh.word_count && is_redir(extend[i]))
			return (error_message("minishell: Syntax error: redirect"));
		i++;
	}
	return (1);
}

int	parse_execs(t_msh *g_msh, t_exec **head)
{
	size_t	i;
	char	**extend;

	i = 0;
	extend = (char **)malloc(sizeof(char *) * (g_msh->word_count + 1));
	while (i < g_msh->word_count)
	{
		extend[i] = extend_str(&g_msh->coms[i].content);
		i++;
	}
	extend[i] = NULL;
	if (check_parsed(extend) == -1)
		return (-1);
	add_to_structure(head, extend, 0);
	find_path(head, g_msh->env_copy);
	free_table(extend);
	return (1);
}
