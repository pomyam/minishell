/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:43:17 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 17:14:19 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_redir_type(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (RDOUT);
	if (ft_strcmp(str, "<") == 0)
		return (RDIN);
	if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC_IN);
	if (ft_strcmp(str, ">>") == 0)
		return (HEREDOC_OUT);
	return (-1);
}

char	*get_redir_file(char *str)
{
	char	*result;

	if (str == NULL || get_redir_type(str) != -1 || ft_strcmp(str, "|") == 0)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_msh.exit_status = 258;
		return (NULL);
	}
	result = ft_strdup(str);
	return (result);
}

int	add_to_redir(char **extend, int *i, t_exec *tmp)
{
	int		b;
	t_redir	*red;

	b = *i;
	red = new_redir();
	red->type = get_redir_type(extend[b]);
	if (red->type == -1)
		return (-1);
	red->file = get_redir_file(extend[b + 1]);
	if (red->file == NULL)
	{
		free_redir(red);
		return (-1);
	}
	*i += 2;
	push_back_red(&tmp->redir, red);
	return (1);
}

int	is_redir(char *str)
{
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}
