/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:11:34 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 11:07:33 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	push_back(t_exec **head, t_exec *new)
{
	t_exec	*i;

	if (*head == NULL)
		*head = new;
	else
	{
		i = *head;
		while (i->next != NULL)
		{
			i = i->next;
		}
		i->next = new;
		new->prev = i;
	}
}

int	cmp_env(char *tmp, char *env)
{
	char	*env_part;
	int		len;

	len = 0;
	while (env[len] != '=')
		len++;
	env_part = ft_substr(env, 0, len);
	if (ft_strcmp(tmp, env_part) == 0)
	{
		free(env_part);
		return (0);
	}
	free(env_part);
	return (1);
}

int	find_in_envp(char *str, t_msh *g_msh)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	while (g_msh->env_copy[i] != NULL)
	{
		if (cmp_env(tmp, g_msh->env_copy[i]) == 0)
		{
			tmp = NULL;
			return (i);
		}
		i++;
	}
	tmp = NULL;
	return (-1);
}

int	is_valid_env(char c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123)
		|| (c > 47 && c < 58) || c == 95)
		return (1);
	return (0);
}

int	contains_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (-1);
}
