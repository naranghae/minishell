/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change_double.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:42:06 by hyopark           #+#    #+#             */
/*   Updated: 2021/06/14 20:37:34 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	change_double_qute_save(t_cmd **tmp, int *ix, int *i, t_st_end *st_end)
{
	char	*free_p;

	st_end->end = *i;
	(*tmp)->cmd[*ix][st_end->end] = '\0';
	free_p = ft_strjoin((*tmp)->cmd[*ix] + st_end->st,
		(*tmp)->cmd[*ix] + st_end->end + *ix);
	free((*tmp)->cmd[*ix]);
	(*tmp)->cmd[*ix] = ft_strjoin((*tmp)->cmd[*ix], free_p);
	free(free_p);
	*i = st_end->end - 1;
}

void	change_double_qute_init(t_cmd **tmp, int *ix, int *i, t_st_end *st_end)
{
	(*tmp)->cmd[*ix][(*i)++] = '\0';
	st_end->st = *i;
	// while ((*tmp)->cmd[*ix][*i] != '\0' && !((*tmp)->cmd[*ix][*i]
	// 	== '\"' && *i > 0 && (*tmp)->cmd[*ix][(*i) - 1] != '\\'))
	// {
	// 	(*i)++;
	// }
	while ((*tmp)->cmd[*ix][*i] != '\0')
	{
		if ((*tmp)->cmd[*ix][*i] == '\\')
		{
			(*i)++;
			if ((*tmp)->cmd[*ix][*i] != '\0')
				(*i)++;
			continue ;
		}
		if ((*tmp)->cmd[*ix][*i] == '"')
			break;
		(*i)++;
	}
}

void	change_double_qute(t_cmd *tmp, int ix, int i, t_st_end *st_end)
{
	while (tmp->cmd[ix][i] != '\0')
	{
		if (!in_doublequote(tmp->cmd[ix], i, 0, 0) && tmp->cmd[ix][i] == '\'')
			i = change_single_qute(tmp, ix, i) - 1;
		if (tmp->cmd[ix][i] == '\0')
			break ;
		if (!in_singlequote(tmp->cmd[ix], i, 0, 0) && tmp->cmd[ix][i] == '\"')
		{
			change_double_qute_init(&tmp, &ix, &i, st_end);
			if (tmp->cmd[ix][i] == '\0' && st_end->st == i)
			{
				tmp->cmd[ix][i - 1] = '"';
				return ;
			}
			if (tmp->cmd[ix][i] != '\0')
			{
				change_double_qute_save(&tmp, &ix, &i, st_end);
				continue ;
			}
			else
				break ;
		}
		i++;
	}
}
