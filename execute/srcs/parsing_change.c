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


char	*find_env(t_cmd *cmd, t_env *env, int idx, int *i)
{
	t_env *tmp;

	tmp = env;
	while(tmp != NULL)
	{
		if (!ft_strncmp(tmp->name, &cmd->cmd[idx][*i], ft_strlen(tmp->name)))
		{
			*i += ft_strlen(tmp->name);
			return(tmp->contents);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	change_env(t_cmd *tmp, t_env *env, int idx, int i)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{
	char *envstr;
	int start;

	while (tmp->cmd[idx][i] != '\0')
	{
		if (tmp->cmd[idx][i] == '\\')
		{
			if (tmp->cmd[idx][i++ + 1] != '\0')
				i += 1;
			continue ;
		}
		if (tmp->cmd[idx][i++] == '$')
		{
			start = i;
			envstr = find_env(tmp, env, idx, &i);
			if (envstr != 0)
				tmp->cmd[idx] = ft_strjoin(ft_strjoin(ft_substr(tmp->cmd[idx], 0, start - 1), envstr),ft_strdup(&(tmp->cmd[idx][i])));
		}
	}
}

void	change_escape(t_cmd **cmd, int idx, int start)
{
	char	*re;
	int		re_i;
	t_cmd	*tmp;

	tmp = *cmd;
	re_i = 0;
	re = tmp->cmd[idx];
	while (tmp->cmd[idx][start] != '\0')
	{
		if (tmp->cmd[idx][start] == '\\')
		{
				if (tmp->cmd[idx][start + 1] != '\0' && (tmp->cmd[idx][start + 1] == '`' || tmp->cmd[idx][start + 1] == '$' || tmp->cmd[idx][start + 1] == '"' || tmp->cmd[idx][start + 1] == '\\'))
				{
					re[re_i++] = tmp->cmd[idx][start + 1];
					start += 2;
				}
				else
					re[re_i++] = tmp->cmd[idx][start++];
			continue ;
		}
		else
			re[re_i++] = tmp->cmd[idx][start];
		start++;
	}
	re[re_i] = '\0';
	(*cmd)->cmd[idx] = re;
}

void	change_double_qute(t_cmd *tmp, int idx, int i)
{
	int start;
	int end;

	while (tmp->cmd[idx][i] != '\0')
	{
		if (!in_doublequote(tmp->cmd[idx],0,ft_strlen(tmp->cmd[idx])) && tmp->cmd[idx][i] == '\"')
			{
				tmp->cmd[idx][i++] = '\0';
				start = i;
				while (tmp->cmd[idx][i] != '\0' && tmp->cmd[idx][i] != '\"')
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

	if (type == 1)
		tmp = (*list)->next;
	else
		tmp = *list;
	while (tmp != tmp->tail)
	{
		idx = 0;
		while (tmp->cmd[idx]!= NULL)
		{
			i = 0;
			if (type == 1)
				change_single_qute(tmp, idx, i);
			else if (type == 2)
			{
				change_env(tmp, env, idx, i);
				change_escape(&tmp, idx, i);
				change_double_qute(tmp, idx, i);
			}
			idx++;
		}
		tmp = tmp->next;
	}
}
