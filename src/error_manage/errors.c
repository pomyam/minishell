/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:01:59 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 10:34:15 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_message(char *str)
{
	printf("Error: %s\n", str);
	g_msh.exit_status = 258;
	return (-1);
}

int	message_errno(int err, char *str)
{
	printf("minishell: %s: %s\n", str, strerror(err));
	g_msh.exit_status = 1;
	return (-1);
}
