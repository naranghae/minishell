/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_save_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:34:37 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/11 13:54:27 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	tokenize_red(t_cmd **tmp, int i, int idx)
{
	char	*free_p;

	if (idx == 0 && ((*tmp)->cmd[idx][i] != '>' || (*tmp)->cmd[idx][i] != '<'
		|| ((*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i + 1] != '>')))
	{
		free((*tmp)->cmd[idx]);
		(*tmp)->cmd[idx] = ft_strdup(" ");
		return ;
	}
	while ((*tmp)->cmd[idx][i] != '\0')
	{
		while ((*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i]
			!= '<' && (*tmp)->cmd[idx][i] != '\0')
			i++;
		if ((*tmp)->cmd[idx][i] == '\0')
			break ;
		(*tmp)->cmd[idx][i] = '\0';
		free((*tmp)->cmd[idx]);
		free_p = ft_strtrim((*tmp)->cmd[idx], " ");
		(*tmp)->cmd[idx] = ft_strtrim((*tmp)->cmd[idx], " ");
		// free(free_p);
		break ;
	}
	if (ft_strlen((*tmp)->cmd[idx]) == 0)
		(*tmp)->cmd[idx] = NULL;
}

void	init_r_v(t_save_red *r_v)
{
	r_v->len = 0;
	r_v->type = 0;
}

void	save_red_cmd_add(t_cmd **tmp, int *i, int *idx, t_save_red *r_v)
{
	while ((*tmp)->cmd[*idx][*i] == ' ' && (*tmp)->cmd[*idx][*i] != '\0')
		(*i)++;
	r_v->start = *i;
	while ((*tmp)->cmd[*idx][*i] != ' ' && (*tmp)->cmd[*idx][*i]
		!= '\0' && (*tmp)->cmd[*idx][*i] != '>' && (*tmp)->cmd[*idx][*i] != '<')
	{
		r_v->len++;
		(*i)++;
	}
	add_back_red(&((*tmp)->red),
	new_red(ft_substr((*tmp)->cmd[*idx], r_v->start, r_v->len), r_v->type));
}

void	save_red_cmd(t_cmd **tmp, int i, int idx)
{
	t_save_red r_v;

	while ((*tmp)->cmd[idx][i] != '\0')
	{
		init_r_v(&r_v);
		while (((*tmp)->cmd[idx][i] != '\0' && is_inquote((*tmp)->cmd[idx], i))
			|| ((*tmp)->cmd[idx][i] != '>' &&
				(*tmp)->cmd[idx][i] != '<' && (*tmp)->cmd[idx][i] != '\0'))
			i++;
		if ((*tmp)->cmd[idx][i] == '<')
			r_v.type = IN;
		else if ((*tmp)->cmd[idx][i] == '>')
			r_v.type = OUT;
		if ((*tmp)->cmd[idx][i] == '\0')
			return ;
		if ((*tmp)->cmd[idx][++i] == '>' && r_v.type == OUT)
			r_v.type += (++i) * 0 + 1;
		save_red_cmd_add(tmp, &i, &idx, &r_v);
	}
	if (r_v.type)
		tokenize_red(tmp, 0, idx);
}

void	save_redirection(t_cmd **list)
{
	t_cmd *tmp;

	tmp = (*list)->next;
	while (tmp != (*list)->tail)
	{
		if (tmp->cmd[1] != NULL)
		{
			save_red_cmd(&tmp, 0, 0);
			save_red_cmd(&tmp, 0, 1);
		}
		else if (tmp->cmd[0] != NULL)
			save_red_cmd(&tmp, 0, 0);
		tmp = tmp->next;
	}
}
