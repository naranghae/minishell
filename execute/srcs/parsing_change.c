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

void change_single_qute(t_cmd **list)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{
	int idx;
	int i;
	int start;
	int end;
	t_cmd *tmp;

	tmp = (*list)->next;
	while (tmp != (*list)->tail)
	{
	idx = 0;
		//printf("list0 %s list1 %s \n",  tmp->cmd[0], tmp->cmd[1]);
		//printf("idx %d , cmd [idx] : %s\n", idx, tmp->cmd[idx]);
		while (tmp->cmd[idx]!= NULL)
		{
			i = 0;
			while (tmp->cmd[idx][i] != '\0')
			{
				if (/*!in_singlequote() &&*/ tmp->cmd[idx][i] == '\'')
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
							// printf("joinre : %s\n", tmp->cmd[idx]);
							i = end - 1;
							continue ;
						}
					}
				i++;
			}
			idx++;
		}
		tmp = tmp->next;
	}
}
