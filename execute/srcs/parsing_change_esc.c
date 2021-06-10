/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change_esc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:39:41 by hyopark           #+#    #+#             */
/*   Updated: 2021/06/10 19:39:48 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	init_e(t_ecs *e, t_cmd **cmd, int *ix)
{
	e->tmp = *cmd;
	e->re_i = 0;
	e->re = e->tmp->cmd[*ix];
}

void	change_escape(t_cmd **cmd, int ix, int st)
{
	t_ecs	e;

	init_e(&e, cmd, &ix);
	while (e.tmp->cmd[ix][st] != '\0')
	{
		if (e.tmp->cmd[ix][st] == '\\')
		{
			if (e.tmp->cmd[ix][st + 1] != '\0' && (e.tmp->cmd[ix][st + 1] == '`'
				|| e.tmp->cmd[ix][st + 1] == '$' || e.tmp->cmd[ix][st + 1]
					== '"' || e.tmp->cmd[ix][st + 1] == '\\'))
			{
				e.re[e.re_i++] = e.tmp->cmd[ix][st + 1];
				st += 2;
			}
			else
				e.re[e.re_i++] = e.tmp->cmd[ix][st++];
			continue ;
		}
		else
			e.re[e.re_i++] = e.tmp->cmd[ix][st];
		st++;
	}
	e.re[e.re_i] = '\0';
	(*cmd)->cmd[ix] = e.re;
}
