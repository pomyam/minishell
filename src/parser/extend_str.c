/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:17:15 by lruncorn          #+#    #+#             */
/*   Updated: 2021/09/15 16:05:51 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_part_to_result(char **result, char *part, t_msh *g_msh)
{
	int		i;
	char	*found;
	char	*tmp;

	i = find_in_envp(part, g_msh);
	if (i != -1)
	{
		found = ft_substr(g_msh->env_copy[i], ft_strlen(part) + 1,
				ft_strlen(g_msh->env_copy[i] + ft_strlen(part) + 1));
		tmp = *result;
		*result = ft_strjoin(*result, found);
		free(tmp);
		free(found);
	}
	return (1);
}

int	get_dollar_loop(int *i, t_dollar *d, char *copy, char **result)
{
	if (d->len != 0)
	{
		d->part = ft_substr(copy, *i + 1, d->len);
		add_part_to_result(result, d->part, &g_msh);
		*i += d->len + 1;
		free(d->part);
		d->part = NULL;
	}
	else
	{
		while (*d->start != '\0' && *d->start != '$')
		{
			add_symbol_to_str(result, d->start - 1, 0, 0);
			d->start++;
			*i += 1;
		}
	}
	return (1);
}

int	get_dollar(char *copy, int *i, char **result)
{
	t_dollar	d;

	d.part = NULL;
	d.start = NULL;
	d.len = 0;
	d.start = &copy[*i + 1];
	if (*result == NULL)
		*result = ft_strnew(1);
	while (is_valid_env(d.start[d.len]))
	{
		if (d.len == 0 && d.start[d.len] >= '0' && d.start[d.len] <= '9')
			break ;
		d.len++;
	}
	get_dollar_loop(i, &d, copy, result);
	if (d.part != NULL)
		free(d.part);
	if (*result == NULL)
		free(*result);
	return (1);
}

int	add_symbol_to_str(char **result, char *copy, int oq, int dq)
{
	char	*tmp;
	char	*new;

	if (*result == NULL)
		*result = ft_strnew(1);
	if ((*copy == '\'' && dq == 0) || (*copy == '\"' && oq == 0))
		return (1);
	new = malloc(sizeof(char) * (ft_strlen(*result) + 2));
	ft_strlcpy(new, *result, (ft_strlen(*result) + 1));
	new[ft_strlen(*result)] = *copy;
	new[ft_strlen(*result) + 1] = '\0';
	tmp = *result;
	*result = new;
	free(tmp);
	return (1);
}

char	*extend_str(char **com)
{
	t_quotes	q;

	init_quotes(&q, com);
	while (q.copy[q.i] != '\0')
	{
		if (q.copy[q.i] == '\"' && q.dq == 0)
			q.dq = 1;
		else if (q.copy[q.i] == '\"' && q.dq == 1)
			q.dq = 0;
		if (q.copy[q.i] == '\'' && q.oq == 0 && q.dq == 0)
			q.oq = 1;
		else if (q.copy[q.i] == '\'' && q.oq == 1 && q.dq == 0)
			q.oq = 0;
		if (q.copy[q.i] == '$' && q.oq == 0)
			get_dollar(q.copy, &q.i, &q.result);
		else
			add_symbol_to_str(&q.result, &q.copy[q.i++], q.oq, q.dq);
	}
	if (ft_strcmp(q.result, "$?") == 0)
	{
		free(q.result);
		q.result = ft_itoa(g_msh.exit_status);
	}
	return (q.result);
}
