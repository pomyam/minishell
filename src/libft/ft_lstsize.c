/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:19 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:28:48 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	n;

	n = 0;
	if (lst != 0)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
			n++;
		}
		if (lst->next == NULL)
			n++;
	}
	return (n);
}
