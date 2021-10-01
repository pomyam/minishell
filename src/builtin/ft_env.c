/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:48:31 by pyamcha           #+#    #+#             */
/*   Updated: 2021/09/15 10:34:15 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(int i)
{
	while (g_msh.env_copy[++i])
		printf("%s\n", g_msh.env_copy[i]);
	g_msh.exit_status = 0;
	return (0);
}
