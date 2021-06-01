/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 202idx/05/11 17:32:19 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/12 11:58:31 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void change_env(t_cmd *tmp, t_env *env, int idx, int i)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{

	// int start;
	// int end;
	
	while (tmp->cmd[idx][i] != '\0')
	{
		if (tmp->cmd[idx][i] == '\\')
		{
			if (tmp->cmd[idx][i++ + 1] != '\0')
				i += 2;
			continue ;
		}
		if (tmp->cmd[idx][i] == '$')
		{
			if (!ft_strncmp(env->name, &tmp->cmd[idx][i], ft_strlen(env->name)))
				ft_strjoin(&tmp->cmd[idx][i], env->contents);
		}
		i++;
	}
}

void change_single_qute(t_cmd *tmp, int idx, int i)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{
	int start;
	int end;

	while (tmp->cmd[idx][i] != '\0')
	{
		if (!in_singlequote(tmp->cmd[idx],0,ft_strlen(tmp->cmd[idx])) && tmp->cmd[idx][i] == '\'')
			{
				tmp->cmd[idx][i++] = '\0';
				start = i;
				while (tmp->cmd[idx][i] != '\0' && tmp->cmd[idx][i] != '\'')
					i++;
				if (tmp->cmd[idx][i] != '\0')
				{
					end = i;
					tmp->cmd[idx][end] = '\0';
					tmp->cmd[idx] = ft_strjoin(tmp->cmd[idx],ft_strjoin(tmp->cmd[idx] + start, tmp->cmd[idx] + end + idx));
					i = end - 1;
					continue ;
				}
			}
		i++;
	}
}

void change_qute(t_cmd **list, t_env *env,int type)
{
	int idx;
	int i;
	t_cmd *tmp;

	tmp = (*list)->next;
	while (tmp != (*list)->tail)
	{
	idx = 0;
		while (tmp->cmd[idx]!= NULL)
		{
			i = 0;
			if (type == 1)
				change_single_qute(tmp, idx, i);
			else if (type == 2)
			{
			//  pass_back_slash(tmp, idx, i);
				change_env(tmp, env, idx, i);
			}
			idx++;
		}
		tmp = tmp->next;
	}
}
