/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:52:53 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/16 20:22:26 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	strjoin_to_str(char *line, char *asd, int i)
{
	char	*tmp;
	char	*str;

	tmp = ft_sec(line);
	str = ft_strjoin(g_msh.dop[find_in_dop(asd, &g_msh)], tmp);
	free(g_msh.dop[find_in_dop(asd, &g_msh)]);
	g_msh.dop[i] = ft_strdup(str);
	free(str);
	free(tmp);
}

int	do_builtin(t_exec *head)
{
	build_in(head->args);
	return (1);
}
