/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change_single.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:38:57 by hyopark           #+#    #+#             */
/*   Updated: 2021/06/10 19:39:24 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int		change_single_qute_if(t_cmd **tmp, int *ix, int *i, t_st_end *st_end)
{
	char	*free_p1;
	char	*free_p2;

	if ((*tmp)->cmd[*ix][*i] != '\0')
	{
		st_end->end = *i;
		(*tmp)->cmd[*ix][st_end->end] = '\0';
		free_p1 = ft_strjoin((*tmp)->cmd[*ix] + st_end->st,
			(*tmp)->cmd[*ix] + st_end->end + *ix);
		free_p2 = ft_strjoin((*tmp)->cmd[*ix], free_p1);
		free((*tmp)->cmd[*ix]);
		(*tmp)->cmd[*ix] = free_p2;
		free(free_p1);
		*i = st_end->end - 1;
		return (st_end->end);
	}
	else
	{
		(*tmp)->cmd[*ix][st_end->st - 1] = '\'';
		return (*i);
	}
}

int		change_single_qute(t_cmd *tmp, int ix, int i)
{
	t_st_end st_end;

	while (tmp->cmd[ix][i] != '\0')
	{
		if ((tmp->cmd[ix][i] == '\'' && tmp->cmd[ix][i + 1] != '\0'))
		{
			tmp->cmd[ix][i++] = '\0';
			if (i > 1 && tmp->cmd[ix][i - 2] == '\\')
			{
				tmp->cmd[ix][i - 2] = '\'';
				break ;
			}
			st_end.st = i;
			while (tmp->cmd[ix][i] != '\0' && tmp->cmd[ix][i] != '\'')
				i++;
			return (change_single_qute_if(&tmp, &ix, &i, &st_end));
		}
		i++;
	}
	return (i);
}
